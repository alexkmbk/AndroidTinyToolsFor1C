package com.alexkmbk.androidtinytools;


import android.Manifest;
import android.os.Build;

import java.util.ArrayList;
import java.util.List;

public class Constants {
    public static final String version = "2_1_23";
    public static final int REQUEST_BLUETOOTH_CONNECT_PERMISSION = 100;

    // Метод, возвращающий актуальные Bluetooth-разрешения для текущей версии Android
    public static String[] getBluetoothPermissions() {
        List<String> permissions = new ArrayList<>();

        // Общие разрешения, которые нужны на всех версиях
        permissions.add(Manifest.permission.BLUETOOTH);
        permissions.add(Manifest.permission.BLUETOOTH_ADMIN);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.S) {
            // Android 12+ требует отдельные разрешения на сканирование и подключение
            permissions.add(Manifest.permission.BLUETOOTH_CONNECT);
            permissions.add(Manifest.permission.BLUETOOTH_SCAN);
        } else {
            // До Android 12 нужно разрешение на местоположение для поиска устройств
            permissions.add(Manifest.permission.ACCESS_FINE_LOCATION);
        }

        return permissions.toArray(new String[0]);
    }

}


