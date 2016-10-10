package com.ysgame.quanhuang.hwgame;

import android.app.Activity;
import android.os.Handler;
import android.os.Message;



public class CppActiveHandle extends Handler
{
	public static final int TYPE_ACTIVE_CLOSE_REQUEST = 1;
	public static final int TYPE_PURCHASE_REQUEST = 2;
	public static final int TYPE_ACTION_CLOSING = 3;
	public static final int TYPE_ACTION_SUCCESS = 4;
	
	public static int curPayCodeType = -1;
	public static String curPayCode = null;
	public static String curPayName = null;
	public static int curPayPrice = 0;
	
	public static String eyeChannel = "dadishu";
	
	
	public static String appId = "249FC5FE5ECD49484A38E231D0A704A6";
	private AppActivity context;
	
	CppActiveHandle(Activity context)
	{
		this.context=(AppActivity )context;
		
	}
	
	@Override
	public void handleMessage(Message msg) {
		super.handleMessage(msg);
		try
		{
			
			
			if(msg.obj=="init"){
				AppActivity.main.initSDK(AppActivity.main.appid,AppActivity.main.appkey);
				AppActivity.main.initView();
			}else{
				PayRequestDef paydef = (PayRequestDef)msg.obj;
				curPayCodeType = paydef.payType;
				curPayCode = paydef.payCode;
				curPayPrice = paydef.price;
				
				switch(msg.what)
				{
				case CppActiveHandle.TYPE_ACTIVE_CLOSE_REQUEST:
					closeRequest();
					break;
				case CppActiveHandle.TYPE_PURCHASE_REQUEST:
					//AppActivity.pay.order(curPayCodeType, curPayCode, curPayPrice);
					break;
				case CppActiveHandle.TYPE_ACTION_SUCCESS:
					System.out.println("pay success!!!!!!!!!!!!!!!!!!");
					paySuccess();
					break;
				}
			}
		}
		catch(Exception e)
		{
			
		}
	}
	
	public static void paySuccess()
	{
		if(CppActiveHandle.curPayCodeType > 0)
		{
			
			System.out.println("paySuccess:"+curPayCodeType+curPayCode);
			CppHelper.payResult(true,curPayCode);
		}
	}
	
	private void closeRequest()
	{
		System.out.println("faild:%%%%%%%%%%%%%%%"+curPayCodeType);
		CppHelper.payResult(false,curPayCode);
	}
}
