package com.hw.database;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteException;


/**
 * SDK用户数据库的数据库接口封�?BR>
 * @author 游戏平台�?���?
 * @version [MCS Client V100R001C10, 2013-4-23]
 */
public class UserDBUtils
{
    /** 数据库名�?*/
    public static final String DB_NAME_USER = "gamesdkdemo";
    
    /** 数据库名称后�?/
    public static final String DB_NAME_SUFFIX = ".db";
    
    /** 数据库版�?*/
    public static final int DB_VERSION = 1;

    /** 打印标记 */
    private static final String TAG = "UserDBUtils";
    
    
    /**
     * 当前使用的用户数据库
     */
    private static UserDBOpenHelper mOpenHelper;
    

    /**
     * 
     * 插入数据
     * @param context 上下�?
     * @param table 数据库名
     * @param values 插入的数据内�?
     * @return 返回�?-1 为失�?
     */
    public static long insert(Context context, String table,
            ContentValues values)
    {
        mOpenHelper = DBOpenManager.getUserDb(context);
        
        if (null == mOpenHelper)
        {
            return -1L;
        }
        
        SQLiteDatabase database = null;
        
        try
        {
            database = mOpenHelper.getWritableDatabase();
        }
        catch (SQLiteException e)
        {
            return -1L;
        }
        
        return database.insert(table, null, values);
    }
    
    /**
     * 执行增�?删�?改操作SQL
     * @param context 上下�?
     * @param sql SQL语句
     */
    public static void execSQL(Context context, String sql)
    {
        mOpenHelper = DBOpenManager.getUserDb(context);
        
        if (null == mOpenHelper)
        {
            return;
        }
        
        SQLiteDatabase database = null;
        
        try
        {
            database = mOpenHelper.getWritableDatabase();
        }
        catch (SQLiteException e)
        {
            return;
        }
        database.execSQL(sql);
    }
    
    /**
     * 
     * 更新数据
     * @param context 上下�?
     * @param table 数据库名�?
     * @param values 更新数据内容
     * @param whereClause 条件
     * @param whereArgs 条件参数
     * @return 返回�?-1 为失�?
     */
    public static int update(Context context, String table,
            ContentValues values, String whereClause, String[] whereArgs)
    {
        mOpenHelper = DBOpenManager.getUserDb(context);
        
        if (null == mOpenHelper)
        {
            return -1;
        }
        
        SQLiteDatabase database = null;
        
        try
        {
            database = mOpenHelper.getWritableDatabase();
        }
        catch (SQLiteException e)
        {
            return -1;
        }
        
        return database.update(table, values, whereClause, whereArgs);
    }
    
    /**
     * 查询
     * @param context 上下�?
     * @param table 数据库名�?
     * @param columns  列名(数组)
     * @param selection 查询条件 (可为�?
     * @param selectionArgs 条件参数�?可为�?
     * @param groupBy 分组字段(可为�?
     * @param having 分组条件字段(可为�?
     * @param orderBy 排序字段(可为�?  
     * @return 返回数据库查询Cursor
     */
    public static Cursor query(Context context, String table, String[] columns,
            String selection, String[] selectionArgs, String groupBy, 
            String having, String orderBy)
    {
        
        mOpenHelper = DBOpenManager.getUserDb(context);
        
        if (null == mOpenHelper)
        {
            return null;
        }
        
        SQLiteDatabase database = null;
        
        try
        {
            database = mOpenHelper.getReadableDatabase();
        }
        catch (SQLiteException e)
        {
            return null;
        }
        
        return database.query(table,
                columns,
                selection,
                selectionArgs,
                groupBy,
                having,
                orderBy);
    }
    
    /**
     * 查询
     * @param context 上下�?
     * @param sql 查询条件SQL语句
     * @param selectionArgs 查询条件参数
     * @return 返回查询�? Cursor
     */
    public static Cursor query(Context context, String sql,
            String[] selectionArgs)
    {
        mOpenHelper = DBOpenManager.getUserDb(context);
        
        if (null == mOpenHelper)
        {
            return null;
        }
        
        SQLiteDatabase database = null;
        
        try
        {
            database = mOpenHelper.getWritableDatabase();
        }
        catch (SQLiteException e)
        {
            return null;
        }
        
        return database.rawQuery(sql, selectionArgs);
    }
     
    /**
     * 查询
     * @param context 上下�?
     * @param table 数据库名�?
     * @param columns 列名(数组)
     * @param selection 查询条件 (可为�?
     * @param selectionArgs 条件参数�?可为�?
     * @param groupBy 分组字段(可为�?
     * @param having 分组条件字段(可为�?
     * @param orderBy 排序字段(可为�?
     * @param limit 指定偏移量和获取的记录数(可为�?
     * @return 返回查询�? Cursor
     */
    public static Cursor query(Context context, String table, String[] columns,
            String selection, String[] selectionArgs, String groupBy,
            String having, String orderBy, String limit)
    {
        mOpenHelper = DBOpenManager.getUserDb(context);
        
        if (null == mOpenHelper)
        {
            return null;
        }
        
        SQLiteDatabase database = null;
        
        try
        {
            database = mOpenHelper.getWritableDatabase();
        }
        catch (SQLiteException e)
        {
            return null;
        }
        
        return database.query(table,
                columns,
                selection,
                selectionArgs,
                groupBy,
                having,
                orderBy,
                limit);
    }
    
    /**
     * 删除
     * 
     * @param context 上下�?
     * @param table 表名
     * @param whereClause 条件
     * @param whereArgs 条件参数�?
     * @return 返回�?-1 为失�?
     */
    public static int delete(Context context, String table, String whereClause,
            String[] whereArgs)
    {
        mOpenHelper = DBOpenManager.getUserDb(context);
        
        if (null == mOpenHelper)
        {
            return -1;
        }
        
        SQLiteDatabase database = null;
        
        try
        {
            database = mOpenHelper.getWritableDatabase();
        }
        catch (SQLiteException e)
        {
            return -1;
        }
        return database.delete(table, whereClause, whereArgs);
    }
    
    /**
     * 关闭当前使用数据�?
     * 
     * @param context 上下�?
     */
    public static void closeDB(Context context)
    {
        mOpenHelper = DBOpenManager.getUserDb(context);
        
        if (null == mOpenHelper)
        {
            return;
        }
        mOpenHelper.getWritableDatabase().close();
    }
    
}
