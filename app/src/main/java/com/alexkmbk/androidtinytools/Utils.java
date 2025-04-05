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

        // Сначала собираем все невыданные разрешения
        for (String permission : Constants.getBluetoothPermissions()) {
            if (ContextCompat.checkSelfPermission(mContext, permission) != PackageManager.PERMISSION_GRANTED) {
                notGrantedPermissions.add(permission);
            }
        }

        // Запрашиваем, если есть хотя бы одно невыданное
        if (!notGrantedPermissions.isEmpty()) {
            ActivityCompat.requestPermissions(
                    mContext,
                    notGrantedPermissions.toArray(new String[0]),
                    Constants.REQUEST_BLUETOOTH_CONNECT_PERMISSION
            );
            return false;
        }

        // Все разрешения уже есть
        return true;
    }

}
