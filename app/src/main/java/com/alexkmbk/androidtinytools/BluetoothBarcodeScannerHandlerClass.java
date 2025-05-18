// Partly, some code was used from this project - // https://infostart.ru/public/926522/
//
package com.alexkmbk.androidtinytools;

import android.Manifest;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.pm.PackageManager;

import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.util.UUID;


public class BluetoothBarcodeScannerHandlerClass {
    private Activity mContext; // activity of 1C:Enterprise
    private long mV8Object; // 1C application context

    // in C/C++ code the function will have name Java_com_alexkmbk_androidtinytools_BluetoothBarcodeScannerHandlerClass_OnBarcode
    static native void OnBarcode(long pObject, String sBarcode);

    private String btAdress;
    private android.bluetooth.BluetoothAdapter btAdapter = null;
    private static final android.bluetooth.BluetoothAdapter BluetoothAdapter = null;
    private BluetoothSocket btSocket = null;
    private BluetoothDevice device = null;
    private InputThread inputThread = null;

    // переменные для потокового чтения сообщений от сканера
    private InputStream inStream = null;


    public BluetoothBarcodeScannerHandlerClass(Activity mContext, String btAdress, long v8Object) {
        this.mContext = mContext;
        this.mV8Object = v8Object;
        this.btAdress = btAdress;
    }



    @SuppressLint("MissingPermission")
    public void StartBluetoothBarcodeScannerHandler() {

        if (!Utils.checkBluetoothPermissions(mContext)) {
            return;
        }
        try {
            System.loadLibrary("AndroidTinyTools_" + Constants.version);
        } catch (UnsatisfiedLinkError e) {
            ToastClass toast = new ToastClass(mContext, e.getMessage());
            toast.toast();
            return;
        }

        // получаем объект устройства
        if (btAdapter == null)
            try {
                btAdapter = BluetoothAdapter.getDefaultAdapter();
            } catch (Exception e) {
                ToastClass toast = new ToastClass(mContext, "Не удалось получить доступ к bluetooth адаптеру.");
                toast.toast();
                return;
            }

        if (btAdapter == null) {
            // отсутствует поддержка работы с блютуз
            ToastClass toast = new ToastClass(mContext, "Отсутствует поддержка работы с bluetooth");
            toast.toast();
        }

        if (!btAdapter.isEnabled()) {
            // Bluetooth выключен. Предложим пользователю включить его.
            ToastClass toast = new ToastClass(mContext, "Bluetooth выключен");
            toast.toast();
            return;
        }

        // подключаемся к сканеру путем указания MAC адреса

        try {
            device = btAdapter.getRemoteDevice(btAdress);
        }catch (Exception e) {
            ToastClass toast = new ToastClass(mContext, "Не удалось получить устройство по MAC адресу");
            toast.toast();
            return;
        }

        if (device == null) {
            ToastClass toast = new ToastClass(mContext, "Не удалось получить устройство по MAC адресу");
            toast.toast();
            return;
        }

        // создаем сокет для чтения из виртуального порта
        // для создания требуется UID текущего приложеня (мы его создали при объявлении переменных)

        if (btSocket != null) {
            try {
                btSocket.close();
                btSocket = null;
            } catch (IOException e) {
                btSocket = null;
            }
        }

        try {
            btSocket = device.createRfcommSocketToServiceRecord(UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"));
            //btSocket = device.createInsecureRfcommSocketToServiceRecord(UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"));
        } catch (IOException e) {
            ToastClass toast = new ToastClass(mContext, "Ошибка создания подключения");
            toast.toast();
        }

        if (btSocket == null) {
            ToastClass toast = new ToastClass(mContext, "Ошибка создания подключения");
            toast.toast();

            return;
        }


        // Discovery is resource intensive.  Make sure it isn't going on
        // when you attempt to connect and pass your message.
        btAdapter.cancelDiscovery();

        // соединение установлено
        try {
            btSocket.connect();
            ToastClass toast = new ToastClass(mContext,  "...Соединение установлено и готово к передачи данных...");
            toast.toast();
        } catch (IOException e) {
            try {
                btSocket.close();
            } catch (IOException e2) {
            }
            ToastClass toast = new ToastClass(mContext,  "Ошибка установки соединения: " + e.getMessage());
            toast.toast();
            return;
        }

        // Получить входящий поток данных
        try {
            inStream = btSocket.getInputStream();
        } catch (IOException e) {
            ToastClass toast = new ToastClass(mContext,  e.getMessage());
            toast.toast();
            return;
        }

        inputThread = new InputThread();
        inputThread.start();

    }

    public void StopBluetoothBarcodeScannerHandler()
    {
        cancel();
    }

    public boolean IsConnected()
    {
        return (btSocket != null && btSocket.isConnected() && inputThread != null && inputThread.isAlive());
    }

    public void cancel() {

        if (!Utils.checkBluetoothPermissions(mContext)) {
            return;
        }

        if (inputThread != null)
        {
            try {
                inputThread.interrupt();
            } catch (SecurityException e) {
            }
            inputThread = null;
        }

        if (inStream != null) {
            try {
                inStream.close();
            } catch (IOException e) {
            }
        }
        if (btSocket != null)
            try {
            btSocket.close();
            btSocket = null;
        }
            catch (IOException e) { }
    }

    private class InputThread extends Thread {

        public void run() {
            byte[] buffer = new byte[1024];  // buffer store for the stream
            int bytes; // bytes returned from read()
            // Прослушиваем InputStream пока не произойдет исключение
            while (true) {
                try {
                    // Read from the InputStream
                    bytes = inStream.read(buffer);        // Получаем кол-во байт и само собщение в байтовый массив "buffer"
                    // преобразуем их в строку
                    String strIncom = new String(buffer, 0, bytes, StandardCharsets.US_ASCII);
                    OnBarcode(mV8Object, strIncom);
                } catch (IOException e) {
                    cancel();
                    break;
                }
            }
        }
    }
}
