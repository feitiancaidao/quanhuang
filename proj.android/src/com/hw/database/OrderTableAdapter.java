package com.hw.database;

import java.util.ArrayList;

import com.sdk.commplatform.entry.BuyInfo;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.util.Log;

public class OrderTableAdapter
{
    private static final String TAG = "OrderTableAdapter";
    
    /**
     * 插入数据�?
     * @param context 上下�?
     * @param model 插入的数据对�?
     * @return -1 为失�?
     */
    public static long insert(Context context, BuyInfo order)
    {
        Log.d(TAG, "insert record:" + order.toString());
        ContentValues values = new ContentValues();
        values.put(OrderInfo.ORDER_ID, order.getSerial());
        values.put(OrderInfo.PRODUCT_ID, order.getProductId());
        values.put(OrderInfo.PRODUCT_NAME, order.getProductName());
        values.put(OrderInfo.PRODUCT_PRICE, order.getProductPrice());
        values.put(OrderInfo.PRODUCT_ORGINAL_PRICE, order.getProductOrginalPrice());
        values.put(OrderInfo.COUNT, order.getCount());
        values.put(OrderInfo.PAY_DESCRIPTION, order.getPayDescription());
        
        return UserDBUtils.insert(context, OrderInfo.ORDER_TABLE, values);
    }
    
    public static BuyInfo queryByOrderId(Context context,
        String orderId)
    {
        BuyInfo order = null;
        Cursor cursor = null;
        try
        {
            cursor =
                UserDBUtils.query(context,
                    OrderInfo.ORDER_TABLE,
                    null,
                    OrderInfo.ORDER_ID + " = ?",
                    new String[] {orderId},
                    null,
                    null,
                    OrderInfo.ID);
            if (null != cursor && cursor.getCount() > 0)
            {
                cursor.moveToFirst();
                while (!cursor.isAfterLast())
                {
                    order = parserOrder(cursor);
                    cursor.moveToNext();
                }
            }
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
        finally
        {
            if (cursor != null)
            {
                cursor.close();
                cursor = null;
            }
        }
        return order;
    }
    
    
    private static BuyInfo parserOrder(Cursor cursor)
    {
        BuyInfo order = new BuyInfo();
        order.setSerial(cursor.getString(cursor.getColumnIndex(OrderInfo.ORDER_ID)));
        order.setProductId(cursor.getString(cursor.getColumnIndex(OrderInfo.PRODUCT_ID)));
        order.setProductName(cursor.getString(cursor.getColumnIndex(OrderInfo.PRODUCT_NAME)));
        order.setProductPrice(cursor.getDouble(cursor.getColumnIndex(OrderInfo.PRODUCT_PRICE)));
        order.setProductOrginalPrice(cursor.getDouble(cursor.getColumnIndex(OrderInfo.PRODUCT_ORGINAL_PRICE)));
        order.setCount(cursor.getInt(cursor.getColumnIndex(OrderInfo.COUNT)));
        order.setPayDescription(cursor.getString(cursor.getColumnIndex(OrderInfo.PAY_DESCRIPTION)));
        return order;
    }
    
    
    public static ArrayList<BuyInfo> query(Context context)
    {
        ArrayList<BuyInfo> orderList = new ArrayList<BuyInfo>();
        Cursor cursor = null;
        try
        {
            cursor =
                UserDBUtils.query(context,
                    OrderInfo.ORDER_TABLE,
                    null,
                    null,
                    null,
                    null,
                    null,
                    OrderInfo.ID);
            
            if (null != cursor && cursor.getCount() > 0)
            {
                cursor.moveToFirst();
                while (!cursor.isAfterLast())
                {
                    orderList.add(parserOrder(cursor));
                    cursor.moveToNext();
                }
            }
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
        finally
        {
            if (cursor != null)
            {
                cursor.close();
                cursor = null;
            }
        }
        return orderList;
    }
    
    /**
     * 删除订单
     * @param context  上下�?
     * @return 结果
     */
    public static long deleteByOrderId(Context context, String orderId)
    {
        Log.d(TAG, "deleteByOrderId: " + orderId);
        return UserDBUtils.delete(context,
            OrderInfo.ORDER_TABLE,
            OrderInfo.ORDER_ID + "= ?",
            new String[] {orderId});
    }
    
    /**
     * 清空
     * @param context  上下�?
     * @return 结果
     */
    public static long delete(Context context)
    {
        Log.d(TAG, "delete");
        return UserDBUtils.delete(context, OrderInfo.ORDER_TABLE, null, null);
    }
    
}
