package com.LFWQSP2641.ZhiNengTiKa;

import org.qtproject.qt.android.bindings.QtActivity;
import java.io.File;
import android.net.Uri;
import android.content.Intent;
import android.os.Build;

public class IntentActivity extends org.qtproject.qt.android.bindings.QtActivity
{
    public static void toSelfSetting(QtActivity activity) {
        Intent mIntent = new Intent();
        mIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        if (Build.VERSION.SDK_INT >= 9) {
            mIntent.setAction("android.settings.APPLICATION_DETAILS_SETTINGS");
            mIntent.setData(Uri.fromParts("package", activity.getPackageName(), null));
        } else if (Build.VERSION.SDK_INT <= 8) {
            mIntent.setAction(Intent.ACTION_VIEW);
            mIntent.setClassName("com.android.settings", "com.android.setting.InstalledAppDetails");
            mIntent.putExtra("com.android.settings.ApplicationPkgName", activity.getPackageName());
        }
        activity.startActivity(mIntent);
    }
    public static void openUrl(String url, QtActivity activity)
    {
        Intent intent = new Intent();
        // 执行动作
        intent.setAction(Intent.ACTION_VIEW);
        // 执行的数据类型
        intent.setDataAndType(Uri.parse(url),"text/html");
        activity.startActivity(intent);
    };

};
