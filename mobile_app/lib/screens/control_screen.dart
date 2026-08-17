import 'package:flutter/material.dart';
import '../main.dart';
import '../services/bluetooth_service.dart';
import '../constants/robot_command.dart';

class ControlScreen extends StatelessWidget {
  const ControlScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Điều Khiển Robot'),
        actions: [
          IconButton(
            icon: Icon(themeNotifier.value == ThemeMode.light ? Icons.dark_mode : Icons.light_mode),
            onPressed: () {
              themeNotifier.value = themeNotifier.value == ThemeMode.light ? ThemeMode.dark : ThemeMode.light;
            },
          ),
          Builder(
            builder: (context) => IconButton(
              icon: const Icon(Icons.settings),
              onPressed: () => Scaffold.of(context).openEndDrawer(),
            ),
          ),
        ],
      ),
      endDrawer: Drawer(
        child: Column(
          children: [
            const DrawerHeader(
              decoration: BoxDecoration(color: Colors.blue),
              child: Center(
                child: Text(
                  'CÀI ĐẶT HỆ THỐNG',
                  style: TextStyle(color: Colors.white, fontSize: 20),
                ),
              ),
            ),
            ListTile(
              leading: const Icon(Icons.bluetooth, color: Colors.blue),
              title: const Text('Kiểm tra Bluetooth'),
              subtitle: const Text('Xem Bluetooth đã bật chưa'),
              onTap: () async {
                Navigator.pop(context);
                bool isEnabled = await BluetoothManager().checkBluetoothStatus();
                
                if (!context.mounted) return;

                if (isEnabled) {
                  ScaffoldMessenger.of(context).showSnackBar(
                    const SnackBar(
                      content: Text('Bluetooth đã được bật!'),
                      backgroundColor: Colors.green,
                    ),
                  );
                } else {
                  ScaffoldMessenger.of(context).showSnackBar(
                    const SnackBar(
                      content: Text('Bluetooth đang tắt. Vui lòng bật lên và kết nối với robot để vào chế độ manualdriver!'),
                      backgroundColor: Colors.red,
                      duration: Duration(seconds: 4),
                    ),
                  );
                }
              },
            ),
            ListTile(
              leading: const Icon(Icons.memory, color: Colors.green),
              title: const Text('Thông tin Robot'),
              subtitle: const Text('Thông số phần cứng'),
              onTap: () {
                Navigator.pop(context);
                showDialog(
                  context: context,
                  builder: (context) => AlertDialog(
                    title: const Row(
                      children: [
                        Icon(Icons.info, color: Colors.blue),
                        SizedBox(width: 10),
                        Text('Thông tin Hệ thống'),
                      ],
                    ),
                    content: const Text(
                      '🤖 Tên Robot: DualModeRobotCar V1\n\n'
                      '🧠 Dòng chip điều khiển: ESP32 DevKit V1\n\n'
                      '📡 Kết nối: Bluetooth (BLE)\n\n'
                      '⚡ Tốc độ Baudrate: 9600'
                    ),
                    actions: [
                      TextButton(
                        onPressed: () => Navigator.pop(context),
                        child: const Text('ĐÓNG'),
                      ),
                    ],
                  ),
                );
              },
            ),
            const Divider(),
            const Padding(
              padding: EdgeInsets.all(16.0),
              child: Text('Version 1.0.0'),
            ),
          ],
        ),
      ),
      body: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          const Text(
            'CHẾ ĐỘ HOẠT ĐỘNG',
            style: TextStyle(fontSize: 16, fontWeight: FontWeight.bold, color: Colors.grey),
          ),
          const SizedBox(height: 10),
          Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              ElevatedButton.icon(
                onPressed: () => BluetoothManager().sendCommand('M'),
                icon: const Icon(Icons.pan_tool, color: Colors.white),
                label: const Text('MANUAL (M)', style: TextStyle(color: Colors.white)),
                style: ElevatedButton.styleFrom(
                  backgroundColor: Colors.orange,
                  padding: const EdgeInsets.symmetric(horizontal: 20, vertical: 15),
                ),
              ),
              const SizedBox(width: 20),
              ElevatedButton.icon(
                onPressed: () => BluetoothManager().sendCommand('A'),
                icon: const Icon(Icons.smart_toy, color: Colors.white),
                label: const Text('AUTO (A)', style: TextStyle(color: Colors.white)),
                style: ElevatedButton.styleFrom(
                  backgroundColor: Colors.green,
                  padding: const EdgeInsets.symmetric(horizontal: 20, vertical: 15),
                ),
              ),
            ],
          ),
          const SizedBox(height: 50),
          ElevatedButton(
            onPressed: () => BluetoothManager().sendCommand(RobotCommand.forward),
            style: ElevatedButton.styleFrom(
              padding: const EdgeInsets.all(20),
              shape: const CircleBorder(),
            ),
            child: const Icon(Icons.arrow_upward, size: 40),
          ),
          const SizedBox(height: 20),
          Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              ElevatedButton(
                onPressed: () => BluetoothManager().sendCommand(RobotCommand.left),
                style: ElevatedButton.styleFrom(
                  padding: const EdgeInsets.all(20),
                  shape: const CircleBorder(),
                ),
                child: const Icon(Icons.arrow_back, size: 40),
              ),
              const SizedBox(width: 15),
              ElevatedButton(
                onPressed: () => BluetoothManager().sendCommand(RobotCommand.stop),
                style: ElevatedButton.styleFrom(
                  padding: const EdgeInsets.all(25),
                  shape: const CircleBorder(),
                  backgroundColor: Colors.redAccent,
                  foregroundColor: Colors.white,
                ),
                child: const Icon(Icons.stop, size: 40),
              ),
              const SizedBox(width: 15),
              ElevatedButton(
                onPressed: () => BluetoothManager().sendCommand(RobotCommand.right),
                style: ElevatedButton.styleFrom(
                  padding: const EdgeInsets.all(20),
                  shape: const CircleBorder(),
                ),
                child: const Icon(Icons.arrow_forward, size: 40),
              ),
            ],
          ),
          const SizedBox(height: 20),
          ElevatedButton(
            onPressed: () => BluetoothManager().sendCommand(RobotCommand.backward),
            style: ElevatedButton.styleFrom(
              padding: const EdgeInsets.all(20),
              shape: const CircleBorder(),
            ),
            child: const Icon(Icons.arrow_downward, size: 40),
          ),
        ],
      ),
    );
  }
}