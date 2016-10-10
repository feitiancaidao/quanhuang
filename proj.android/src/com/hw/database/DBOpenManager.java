package com.hw.database;

import android.content.Context;

/**
 * SDK数据管理�?BR>
 * @author 游戏平台�?���?
 * @version [MCS Client V100R001C10, 2013-4-23]
 */
public class DBOpenManager
{
    /**
     * 用户数据�?
     */
    private static UserDBOpenHelper userDb;
    
    /**
     * 获取用户相关的数据库<BR>
     * @param context 上下�?
     * @return 获取到指定用户的数据�?
     */
    public static synchronized UserDBOpenHelper getUserDb(Context context)
    {

        if (userDb == null)
        {
            userDb = new UserDBOpenHelper(context);
        }
        return userDb;
    }
    
}
