package com.hw.database;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteDatabase.CursorFactory;
import android.database.sqlite.SQLiteOpenHelper;

/**
 * SDK鐢ㄦ埛鏁版嵁鐨勫疄浣�BR>
 * @author 娓告垙骞冲彴寮�彂缁�? * @version [MCS Client V100R001C10, 2013-4-23]
 */
public class UserDBOpenHelper extends SQLiteOpenHelper
{
    
    /**
     * [鍒涘缓鐢ㄦ埛鐩稿叧鐨勬暟鎹簱]
     * @param context 涓婁笅鏂�?     */
    public UserDBOpenHelper(Context context)
    {
        this(context, UserDBUtils.DB_NAME_USER + UserDBUtils.DB_NAME_USER, null,
            UserDBUtils.DB_VERSION);
    }
    
    /**
     * 鐢ㄦ埛鏁版嵁搴撶殑鏋勯�鍑芥�?
     * @param context 涓婁笅鏂�?     * @param name 鏁版嵁搴撳悕
     * @param factory cursor宸ュ�?
     * @param version 鏁版嵁鐗堟湰
     */
    public UserDBOpenHelper(Context context, String name, CursorFactory factory, int version)
    {
        super(context, name, factory, version);
    }
    
    /**
     * 鐢ㄦ埛鏁版嵁搴搊nCreate鏂规�?
     * @param db 鏁版嵁搴�?     * @see android.database.sqlite.SQLiteOpenHelper#onCreate(android.database.sqlite.SQLiteDatabase)
     */
    @Override
    public final void onCreate(SQLiteDatabase db)
    {
        /**
         * 鍒涘缓鏂囦欢澶硅鍥剧洰褰曠紦�?樿�?
         */
        db.execSQL(OrderInfo.CREATE_TABLE_STR.toString());
        
        //鍒涘缓鐢ㄦ埛閰嶇疆椤硅�?
        createUserConfigDb(db);
    }
    
    /**
     * 鍒涘缓鐢ㄦ埛閰嶇疆椤硅�?骞跺垵濮嬪寲鐩稿叧鐨勯厤缃」鏁版嵁<BR>
     * [鍔熻兘璇︾粏鎻忚堪]
     * @param db
     */
    private void createUserConfigDb(SQLiteDatabase db)
    {
    }
    
    /**
     * 褰撴暟鎹簱鐗堟湰鍙戠敓鍙樺�?褰撲互鍚庢湁鏁版嵁搴撳彉鍔ㄧ殑鏃跺�锛岃鍒ゆ柇鐗堟湰杩涜鏁版嵁鍓叉帴
     * @param db 鏁版嵁搴�?     * @param oldVersion 鏁版嵁搴撹�鐗堟�?
     * @param newVersion 鏁版嵁搴撴柊鐗堟�?
     */
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion)
    {
    }
    
}
