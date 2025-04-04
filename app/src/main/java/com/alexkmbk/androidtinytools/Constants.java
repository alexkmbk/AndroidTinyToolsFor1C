package com.alexkmbk.androidtinytools;


import android.Manifest;

public class Constants {
    public static final String version = "2_1_20";
    public static final int REQUEST_BLUETOOTH_CONNECT_PERMISSION = 100;

    public static final String[] BluetoothPermissions = {Manifest.permission.BLUETOOTH_CONNECT,
            Manifest.permission.BLUETOOTH,
            Manifest.permission.BLUETOOTH_ADMIN,
            Manifest.permission.BLUETOOTH_SCAN};
}


