package com.alexkmbk.androidtinytools;

import android.app.Activity;
import android.bluetooth.BluetoothDevice;
import java.util.Set;

import static android.content.Context.VIBRATOR_SERVICE;

public class BluetoothClass {
    Activity mContext;
    private static final android.bluetooth.BluetoothAdapter BluetoothAdapter = null;
    private Set<BluetoothDevice> pairedDevices;
    private StringBuilder TextOfDevice = new StringBuilder();
    public static String BaseName;
    private android.bluetooth.BluetoothAdapter btAdapter = null;

    public BluetoothClass(Activity mContext) {
        this.mContext = mContext;
    }

    public String getBluetoothDevicesList()
    {
        // Get the local Bluetooth adapter
        btAdapter = BluetoothAdapter.getDefaultAdapter();
        if(btAdapter==null)
        {
            // отсутствует поддержка работы с блютуз
            //Toast.makeText(mContext.getApplicationContext(), "Отсутствует поддержка работы с bluetooth", Toast.LENGTH_SHORT).show();
            return "";
        }
        if (!btAdapter.isEnabled()) {
            // Bluetooth выключен. Предложим пользователю включить его.
            //Toast.makeText(mContext.getApplicationContext(), "Bluetooth выключен", Toast.LENGTH_SHORT).show();
            return "";
        }

        // Get a set of currently paired devices
        pairedDevices = btAdapter.getBondedDevices();

        // If there are paired devices, add each one to the ArrayAdapter
        if (pairedDevices.size() > 0) {
            for (BluetoothDevice device : pairedDevices) {
                TextOfDevice.append(device.getName() + "///" + device.getAddress() + "\n");
            }
        } else {
            String noDevices = "No devices found";
            TextOfDevice.append(noDevices);
        }
        return TextOfDevice.toString();
    }
}
