package com.alexkmbk.androidtinytools;

import android.Manifest;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothManager;

import java.util.Set;

public class BluetoothClass {
    Activity mContext;
    private static final android.bluetooth.BluetoothAdapter BluetoothAdapter = null;
    private Set<BluetoothDevice> pairedDevices;
    private StringBuilder TextOfDevice = new StringBuilder();
    private android.bluetooth.BluetoothAdapter btAdapter = null;

    public BluetoothClass(Activity mContext) {
        this.mContext = mContext;
    }

    @SuppressLint("MissingPermission")
    public String getBluetoothDevicesList() {

        if (!Utils.checkBluetoothPermissions(mContext)) {
            return "";
        }
        // Get the local Bluetooth adapter
        //btAdapter = BluetoothAdapter.getDefaultAdapter();

        BluetoothManager bluetoothManager = (BluetoothManager) mContext.getSystemService(mContext.BLUETOOTH_SERVICE);
        btAdapter = bluetoothManager.getAdapter();

        if (btAdapter == null) {
            // отсутствует поддержка работы с блютуз
            ToastClass toast = new ToastClass(mContext, "Отсутствует поддержка работы с bluetooth");
            toast.toast();
            return "";
        }
        if (!btAdapter.isEnabled()) {
            // Bluetooth выключен. Предложим пользователю включить его.
            ToastClass toast = new ToastClass(mContext, "Bluetooth выключен");
            toast.toast();
            return "";
        }

        pairedDevices = btAdapter.getBondedDevices();

        // If there are paired devices, add each one to the ArrayAdapter
        if (pairedDevices.size() > 0) {
            for (BluetoothDevice device : pairedDevices) {
                TextOfDevice.append(device.getName() + "///" + device.getAddress() + "\n");
            }
        } else {
            ToastClass toast = new ToastClass(mContext, "Не найдено ни одного устройства.");
            toast.toast();
            return "";
        }
        return TextOfDevice.toString();
    }
}
