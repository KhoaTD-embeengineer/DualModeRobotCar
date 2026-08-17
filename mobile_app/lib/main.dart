import 'package:flutter/material.dart';
import 'screens/control_screen.dart';
import 'screens/devicelistscreen.dart';
void main() {
  runApp(const RobotControllerApp());
}

ValueNotifier<ThemeMode> themeNotifier = ValueNotifier(ThemeMode.light);

class RobotControllerApp extends StatelessWidget {
  const RobotControllerApp({super.key});

  @override
  Widget build(BuildContext context) {
    return ValueListenableBuilder<ThemeMode>(
      valueListenable: themeNotifier,
      builder: (_, currentMode, __){
        return MaterialApp(
          title: 'Robot Controller',
          debugShowCheckedModeBanner: false,
          theme: ThemeData(
            primarySwatch: Colors.blue,
            useMaterial3: true,
            brightness: Brightness.light,
          ),
          darkTheme: ThemeData(
            brightness: Brightness.dark,
            useMaterial3: true,
          ),
          themeMode: currentMode,
          home: const DeviceListScreen(),
        );
      },
    );
  }
}