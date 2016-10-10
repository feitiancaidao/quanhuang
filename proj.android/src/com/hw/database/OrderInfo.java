package com.hw.database;

public class OrderInfo
{
    /**
     * 表名
     */
    public static final String ORDER_TABLE = "OrderTable";
    
    /**
     * 自增长ID
     */
    public static final String ID = "_id";
    
    public static final String ORDER_ID = "orderId";
    
    public static final String PRODUCT_ID = "product_id";
    
    public static final String PRODUCT_NAME = "product_name";
    
    public static final String PRODUCT_PRICE = "product_price";
    
    public static final String PRODUCT_ORGINAL_PRICE = "product_orginal_price";
    
    public static final String COUNT = "count";

    public static final String PAY_DESCRIPTION = "pay_description";

    /**
     * 构�?创建数据库的执行语句
     */
    public static final StringBuffer CREATE_TABLE_STR =
        new StringBuffer().append("create table ")
            .append(ORDER_TABLE)
            .append("(")
            .append(ID)
            .append(" INTEGER primary key autoincrement,")
            .append(ORDER_ID)
            .append(" text,")
            .append(PRODUCT_ID)
            .append(" text,")
            .append(PRODUCT_NAME)
            .append(" text,")
            .append(PRODUCT_PRICE)
            .append(" double,")
            .append(PRODUCT_ORGINAL_PRICE)
            .append(" double,")
            .append(COUNT)
            .append(" integer,")
            .append(PAY_DESCRIPTION)
            .append(" text")
            .append(")");
}
