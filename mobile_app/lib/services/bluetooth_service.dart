import 'dart:async';
import 'dart:convert';
import 'package:flutter/foundation.dart';
import 'package:flutter_blue_plus/flutter_blue_plus.dart';

class BluetoothManager {
  // Singleton pattern
  static final BluetoothManager _instance = BluetoothManager._internal();
  factory BluetoothManager() => _instance;
  BluetoothManager._internal();

  BluetoothDevice? connectedDevice;
  BluetoothCharacteristic? _writeCharacteristic;
  StreamSubscription<BluetoothConnectionState>? _connectionStateSubscription;

  bool get isConnected => connectedDevice != null;

  final String serviceUuid = "6E400001-B5A3-F393-E0A9-E50E24DCCA9E";
  final String rxUuid = "6E400002-B5A3-F393-E0A9-E50E24DCCA9E";

  Future<bool> checkBluetoothStatus() async {
    if (await FlutterBluePlus.isSupported == false) {
      debugPrint("Thiết bị không hỗ trợ Bluetooth");
      return false;
    }
    final state = await FlutterBluePlus.adapterState.first;
    return state == BluetoothAdapterState.on;
  }

  Future<bool> connectToDevice(BluetoothDevice device) async {
    try {
      await device.connect(timeout: const Duration(seconds: 5));
      connectedDevice = device;

      _connectionStateSubscription = device.connectionState.listen((state) {
        if (state == BluetoothConnectionState.disconnected) {
          disconnect();
        }
      });

      List<BluetoothService> services = await device.discoverServices();
      for (var service in services) {
        if (service.uuid.toString().toUpperCase() == serviceUuid) {
          for (var characteristic in service.characteristics) {
            if (characteristic.uuid.toString().toUpperCase() == rxUuid) {
              _writeCharacteristic = characteristic;
              debugPrint("Đã kết nối và cấu hình cổng điều khiển thành công!");
              return true;
            }
          }
        }
      }
      debugPrint("Lỗi: Không tìm thấy UART Service trên thiết bị này.");
      return false;
    } catch (e) {
      debugPrint("Lỗi kết nối: $e");
      await disconnect();
      return false;
    }
  }

  Future<void> disconnect() async {
    _connectionStateSubscription?.cancel();
    if (connectedDevice != null) {
      await connectedDevice!.disconnect();
    }
    connectedDevice = null;
    _writeCharacteristic = null;
    debugPrint("Đã ngắt kết nối.");
  }

  Future<void> sendCommand(String command) async {
    if (_writeCharacteristic == null) {
      debugPrint("Cảnh báo: Chưa kết nối, không thể gửi lệnh.");
      return;
    }
    try {
      List<int> bytes = utf8.encode(command);
      await _writeCharacteristic!.write(bytes, withoutResponse: true);
      debugPrint("Đã gửi lệnh: $command");
    } catch (e) {
      debugPrint("Lỗi gửi dữ liệu: $e");
    }
  }
}