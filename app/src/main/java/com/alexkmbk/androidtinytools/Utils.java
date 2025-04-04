package com.alexkmbk.androidtinytools;

import android.Manifest;
import android.app.Activity;
import android.content.pm.PackageManager;

import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import java.util.ArrayList;

public class Utils {
    public static boolean checkBluetoothPermissions(Activity mContext) {

        ArrayList<String> notGrantedPermissions = new ArrayList<>();
        for (String permission : Constants.BluetoothPermissions) {
            if (ContextCompat.checkSelfPermission(mContext, permission) != PackageManager.PERMISSION_GRANTED) {
                notGrantedPermissions.add(permission);
            }

            if (!notGrantedPermissions.isEmpty()) {
                // Request the permissions that are not granted
                ActivityCompat.requestPermissions(mContext, notGrantedPermissions.toArray(new String[0]),
                        Constants.REQUEST_BLUETOOTH_CONNECT_PERMISSION);
                return false;
            }
        }
        return true;
    }
}
