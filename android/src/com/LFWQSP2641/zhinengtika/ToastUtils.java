package com.LFWQSP2641.ZhiNengTiKa;

import org.qtproject.qt.android.bindings.QtActivity;
import java.lang.Runnable;
import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;
import java.lang.reflect.Field;
import androidx.core.app.NotificationManagerCompat;
import android.widget.Toast;

public class ToastUtils extends org.qtproject.qt.android.bindings.QtActivity {
    private static Object iNotificationManagerObj;

    /**
     * @param activity
     * @param message
     */
    public static void show(QtActivity activity, String message) {
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                show(activity, message, Toast.LENGTH_SHORT);
            }
        });
    }

    /**
     * @param activity
     * @param message
     */
    public static void show(QtActivity activity, String message, int duration) {
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (message == null || message.length() == 0) {
                    return;
                }
                //后setText 兼容小米默认会显示app名称的问题
                Toast toast = Toast.makeText(activity, null, duration);
                toast.setText(message);
                toast.show();
            }
        });
    }
}
