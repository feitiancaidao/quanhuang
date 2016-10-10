/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.ysgame.quanhuang.hwgame;

import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.cocos2dx.lib.Cocos2dxActivity;


import com.hw.database.OrderTableAdapter;


import com.sdk.commplatform.CallbackListener;
import com.sdk.commplatform.Commplatform;
import com.sdk.commplatform.ErrorCode;
import com.sdk.commplatform.MiscCallbackListener;
import com.sdk.commplatform.entry.AppInfo;
import com.sdk.commplatform.entry.BuyInfo;
import com.sdk.commplatform.entry.PayResult;
import com.sdk.commplatform.entry.Payment;
import com.sdk.commplatform.entry.QueryPayment;
import com.sdk.commplatform.entry.PaymentState;

//import android.R;
import android.app.ProgressDialog;
import android.content.Context;
import android.os.Bundle;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.widget.Toast;

import com.sdk.commplatform.entry.SkuDetail;



public class AppActivity extends Cocos2dxActivity {
	
	private static final String TAG = "AppActivity";
	public  static CppActiveHandle cppHandle = null;
	private ProgressDialog mProgressDialog;
	public boolean initfinished=false;
	
	public static AppActivity main;
	public static Context ctx;
	public static boolean isFinished=false; 
	public static boolean sdkinit=false;
	public AppInfo appInfo;
	
	public int appid;
	public String appkey;
	public String yaoshi="ysgame";
	
	private boolean isPaying=false;
	
	private Map propInfos =new HashMap();
	
	public int count=0;
	
	@Override
	protected void onCreate(Bundle savedInstanceState)    {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		main=this;
		ctx=AppActivity.this;
		
			appid=Integer.valueOf( this.getString(R.string.appid) );
			appkey=this.getString(R.string.appkey);
		
		
		cppHandle = new CppActiveHandle(this);
		thread();
		
		initView();
		//initSDK(appid,appkey);
		//checkResult();	
	} 
	
	private void thread(){
		new Thread() {
			public void run() {
				Looper.prepare();
				Message message = new Message();
				message.obj = "init";
				cppHandle.sendMessage(message);
				Looper.loop();
			};
		}.start();
	}
	
  
	
	public void checkResult(){
		
		ArrayList<BuyInfo> orderList=OrderTableAdapter.query(this);
		if (orderList != null && orderList.size() > 0) {
			for (BuyInfo order : orderList) {
				checkPay(order);
				OrderTableAdapter.deleteByOrderId(AppActivity.this,
                        order.getSerial());
			}
		}
	}
	
	public void checkPay(final BuyInfo order)
	{
		final String tradeno=order.getSerial();
		final String productId=order.getProductId();
		if(tradeno==null||tradeno.trim().equals("".trim()))
		{
//			Toast.makeText(this,
//	                "empty tradenos",
//	                Toast.LENGTH_SHORT).show();
	            return;
		}
		showProgressDialog();
		QueryPayment queryPayment = new QueryPayment();
        queryPayment.setTradeNo(tradeno);
		
        
        Commplatform.getInstance().queryPayment(queryPayment,
                this,
                new CallbackListener<PaymentState>()
                {
                    @Override
                    public void callback(int responseCode, PaymentState state)
                    {
                        Log.i("checkResult", "queryPayment responseCode = "
                            + responseCode);
                        dismissProgressDialog();
                        
                        if (responseCode == ErrorCode.COM_PLATFORM_SUCCESS)
                        {
//                            Toast.makeText(AppActivity.main,
//                                "order " + tradeno + " pay success.",
//                                Toast.LENGTH_LONG).show();
                            CppHelper.payResult(true, productId);
                        }
                        else if (responseCode == ErrorCode.COM_PLATFORM_ERROR_UNEXIST_ORDER)
                        {
//                            Toast.makeText(AppActivity.main,
//                                "order " + tradeno + " order unexist.",
//                                Toast.LENGTH_LONG).show();
                            CppHelper.payResult(false, productId);
                        }
                        else if (responseCode == ErrorCode.COM_PLATFORM_ERROR_PAY_FAILURE)
                        {
//                            Toast.makeText(AppActivity.main,
//                                "order " + tradeno + " pay failed.",
//                                Toast.LENGTH_LONG).show();
                            CppHelper.payResult(false, productId);
                        }
                        else if (responseCode == ErrorCode.COM_PLATFORM_ERROR_SERVER_RETURN_ERROR)
                        {
//                            Toast.makeText(AppActivity.main,
//                                "order " + tradeno + " pay failed.",
//                                Toast.LENGTH_LONG).show();
                            CppHelper.payResult(false, productId);
                        }
                        else if (responseCode == ErrorCode.COM_PLATFORM_ERROR_PAY_REQUEST_SUBMITTED)
                        {
//                            Toast.makeText(AppActivity.main,
//                                "order " + tradeno + " order has submitted.",
//                                Toast.LENGTH_LONG).show();
                            CppHelper.payResult(false, productId);
                        }
                        else
                        {
//                            Toast.makeText(AppActivity.main,
//                                "order " + tradeno + " unkown error pay failed.",
//                                Toast.LENGTH_LONG).show();
                            CppHelper.payResult(false, productId);
                        }
                    }
                });
	}
	
	
	
	
	
	
	public static byte[] long2Bytes(long num) {  
	    byte[] byteNum = new byte[8];  
	    for (int ix = 0; ix < 8; ++ix) {  
	        int offset = 64 - (ix + 1) * 8;  
	        byteNum[ix] = (byte) ((num >> offset) & 0xff);  
	    }  
	    return byteNum;  
	}
	
	//闁兼儳鍢茶ぐ鍥⒕韫囨梹绨氶悹浣靛灩瀹曠喖宕ｉ敓锟�?	
	private byte[] getSecurityRandom()
    {
        final int offset = 123456; // offset濞戞挸鎼ù鎰拷瑙勮壘閿熶粙鏁嶅畝鍕級闁稿繐绉烽·鍡涙偖濠婂啫鐓傜紒澶婄Т閻℃瑩寮堕妷锔剧埍闁挎稑鐗嗛幏鎵拷闈涙閻栨粎锟芥冻缂氶懙鎴︽儍閸曨偄顫alt闁哄牆顦遍崑锝囩尵鐠佽櫕濡ч柨娑虫嫹        
        long seed = System.currentTimeMillis() + offset;
        //SecureRandom secureRandom1;
        byte[] bytes = long2Bytes(seed);
        
//        try
//        {
//            secureRandom1 = SecureRandom.getInstance("SHA1PRNG");
//            secureRandom1.setSeed(seed);
//            secureRandom1.nextBytes(bytes);
//        }
//        catch (NoSuchAlgorithmException e)
//        {
//            e.printStackTrace();
//        }
       // Log.i("AsynPayActivity", "getSecurityRandom = " + bytes.toString());
        return bytes;
    }
	

public void initView()
{
    
    boolean isDebug=true;
	
	
	Commplatform.getInstance().SetDebugMode(AppActivity.this,
			isDebug,
            0,
            0);
            
}

/**
 * 闁告帗绻傞‖濠囧礌閺堫枈K
 */
public void initSDK(int appid, String appkey)
{
   
    
    AppInfo appInfo = new AppInfo();
    
    appInfo.setAppId(appid);// 閹煎瓨姊婚弫顥疍
    appInfo.setAppKey(appkey);// 閹煎瓨姊婚弫顥眅y
    appInfo.setCtx(main);
   
    
    /*
     * VersionCheckLevelNormal 闁绘鐗婂﹢鏉课涢敓鐣屽弨濠㈡儼绮剧憴锕傚矗椤栨瑤绨扮紓浣堝懐鏁鹃弶鈺傜椤㈡垵銆掗崨濠傜亞 VersionCheckLevelStrict
     * 闁绘鐗婂﹢鏉课涢敓鐣屽弨濠㈡儼绮剧憴锕傚礆濞嗗海鐟濋柤绛规嫹?缁绘﹢宕楅妷锔惧煑闁硅揪鎷峰娑欘焾椤撳宕ｉ弽褝鎷峰☉鎾额嚈ersionCheckLevelStrict
     */
    appInfo.setVersionCheckStatus(AppInfo.VERSION_CHECK_LEVEL_STRICT);
    
 // 初始化SDK
		Commplatform.getInstance().Init(0, appInfo,
				new CallbackListener<Integer>() {
					@Override
					public void callback(final int paramInt, Integer paramT) {

						// TODO Auto-generated method stub
						if (paramInt == ErrorCode.COM_PLATFORM_SUCCESS) {

//							Toast.makeText(main, "SDK init success",
//									Toast.LENGTH_SHORT).show();
							Log.e("SDK_init","SDK init success");
							getProp();
							checkResult();
							AppActivity.sdkinit=true;

						} else if (paramInt == ErrorCode.COM_PLATFORM_ERROR_FORCE_CLOSE) {
							// init failure
//							Toast.makeText(main, "SDK init close",
//									Toast.LENGTH_SHORT).show();
						//	finish();
							Log.e("SDK_init","SDK init close");
							AppActivity.sdkinit=false;
						} else if (paramInt == ErrorCode.COM_PLATFORM_ERROR_ONLINE_CHECK_FAILURE) {
							// network not connect
//							Toast.makeText(main, "SDK init failed",
//									Toast.LENGTH_SHORT).show();
							//finish();
							Log.e("SDK_init","SDK init online failure");
							AppActivity.sdkinit=false;
						}

					}
				});
 						
 						
 					
 				
}

public void pay(String payid)
{
	isPaying=true;
	final String id= payid;
	//Log.i(TAG,
    //        "paypaypay--- = " + id);
	//Log.i("AsynPayActivity", "finishPayProcess buyInfo = " + buyInfo.toString());
    //闁告艾鏈鐐哄绩椤栨瑧锟�?
	Payment order = null;
    try
    {
        order = getBuyInfo(id);
    }
    catch (Exception e)
    {
    	if(sdkinit==false)
    	{
    		main.runOnUiThread(new Runnable(){

				@Override
				public void run() {
					// TODO Auto-generated method stub
					Toast.makeText(AppActivity.main.ctx,"sdk init is not ready or failed, wait a moment or check your newworks", 
							Toast.LENGTH_SHORT).show();
				}		
    		});
    	}
        order = null;
//        Toast.makeText(ctx,
//            "not have order !",
//            Toast.LENGTH_SHORT).show();
        CppHelper.payResult(false,payid);
        return;
    }
    
    if (order == null)
    {
    	
    	
    	 CppHelper.payResult(false,payid);
        return;
    }
    
    final String productId=order.getProductId();
    final String orderId=order.getTradeNo();
    
    
    saveTradeNo(order);
    
   // payResult(true, 1, productId);
    
    /*
     * CHANGE
     * 
     * */
    
    Commplatform.getInstance().UniPayExt(order, this, new CallbackListener<PayResult>(){

		@Override
		public void callback(final int code,final PayResult arg1) {
			// TODO Auto-generated method stub
			{
                runOnUiThread(new Runnable()
                {
                    public void run()
                    {
                        //回调结果，即支付过程结束
                        isPaying = false;
                        
                        if (code == ErrorCode.COM_PLATFORM_SUCCESS)
                        {
                            //TODO Example 1
                            //根据final 的    productID 或者 orderId 去处理商品，比如查询道具，发放道具等
                            
                            //TODO  Example 2
                            //可以根据订单号查询订单详细信息,在做订单的处理，比如查询道具，发放道具等
                            //如下：
//                            Toast.makeText(ctx,
//                                "pay success",
//                                Toast.LENGTH_SHORT).show();
                            Log.i(TAG, "COM_PLATFORM_SUCCESS");
                            CppHelper.payResult(true, productId);
                        }
                        else if (code == ErrorCode.COM_PLATFORM_ERROR_PAY_FAILURE)
                        {
//                            Toast.makeText(ctx,
//                               "failed",
//                                Toast.LENGTH_SHORT).show();
                            Log.i(TAG,
                                "COM_PLATFORM_ERROR_PAY_FAILURE");
                            CppHelper.payResult(false, productId);
                        }
                        else if (code == ErrorCode.COM_PLATFORM_ERROR_PAY_CANCEL)
                        {
//                            Toast.makeText(ctx,
//                               "cancelled",
//                                Toast.LENGTH_SHORT).show();
                            Log.i(TAG,
                                "COM_PLATFORM_ERROR_PAY_CANCEL");
                            CppHelper.payResult(false, productId);
                        }
                        else
                        {
//                            Toast.makeText(ctx,
//                                "Purchase failed. Error code:"
//                                    + code,
//                                Toast.LENGTH_SHORT).show();
                            Log.i(TAG, "COM_PLATFORM_ERROR_UNKNOWN");
                            CppHelper.payResult(false, productId);
                        }                      
                    }
                });
		
			}	
		}
    });
    
    
}

    
    
public void saveTradeNo(Payment payment)
{
	BuyInfo order=new BuyInfo();
	order.setProductId(payment.getProductId());
	order.setSerial(payment.getTradeNo());
	
	OrderTableAdapter.insert(this, order);
}
    
    
    
    
public void closeGame()
{
	Commplatform.getInstance().gameResumeOrExit(AppActivity.main.ctx,
			new CallbackListener<Integer>() 
			{
				@Override
				public void callback(int arg0, Integer arg1) 
				{
						Log.i("CppHelper", "resumeListener result = " + arg0);
//						Toast.makeText(AppActivity.main.ctx,"jixugame", 
//						Toast.LENGTH_SHORT).show();
				//闁拷閸戝搫绠嶉崨濠囷拷?锟界悮顐㈠彠闂傤叏绱濋悽銊﹀煕閸欐牗绉烽柅锟介崙鐚寸礉缂佈呯敾濞撳憡锟�?
				}
			},
			new CallbackListener<Integer>() 
			{
			@Override
					public void callback(int arg0, Integer arg1) 
					{
//						Toast.makeText(AppActivity.main.ctx,"tuichugame", 
//						Toast.LENGTH_SHORT).show();
						//閻€劍鍩涚涵顔款吇闁拷閸戠尨绱濋崗鎶芥４濞撳憡锟�?
						finish();
						//Util.finishAllActivity();
						//android.os.Process.killProcess(android.os.Process.myPid());
						CppHelper.exitGame();
					}
			});
}



private Payment getBuyInfo(String id)
{//闁哄稄绻濋悰娆撳疮閸℃鎯傚ǎ鍥ｅ墲閿燂拷? 
	
	Payment p=new Payment();
	
	Payment prop=(Payment) propInfos.get(id);
	
	
	p.setTradeNo(getSecurityRandom().toString());
	p.setProductId(prop.getProductId());
	p.setSubject(prop.getSubject());
	p.setAmount(prop.getAmount());
	p.setDesc(prop.getDesc());
	p.setCurrency(prop.getCurrency());
	
	
	
    double allPrice =p.getAmount();
    if (allPrice > 1000000)
    {
//        Toast.makeText(this,
//            "transaction_amount_limit",
//            Toast.LENGTH_SHORT).show();
        return null;
    }
   
    Log.e("getBuyInfo",p.getSubject());
   
    return p;
}

public void getProp(){
	
	Commplatform.getInstance().getSkuDetails(this,
			new CallbackListener<List<SkuDetail>>()
			{

			@SuppressWarnings("unchecked")
			@Override
			public void callback(int errorCode, List<SkuDetail> skuDetails)
			{
			if (errorCode == ErrorCode.COM_PLATFORM_SUCCESS && skuDetails != null)
			{
				StringBuffer buffer = new StringBuffer();
				buffer.append("total = ").append(skuDetails.size()).append("\n");
				for (SkuDetail detail:skuDetails)
				{
					Payment p=new Payment();
					
					
					
					p.setProductId(detail.productId);
					p.setSubject(detail.title);
					p.setAmount(detail.price_amount);
					p.setDesc(detail.description);
					p.setCurrency(detail.price_currency_code);
					
					propInfos.put(p.getProductId(), p);
					
//					Payment p=new Payment();
//					p.setProductId(detail.productId);
//			        p.setSubject(detail.title);
//			        p.setAmount(detail.price_amount);
//			        p.setDesc(detail.description);
//			        p.setTradeNo(detail.productId);
//			        p.setCurrency(detail.price_currency_code);
//			        orderList.add(p);
			        
//					buffer.append("productId = ").append(detail.productId).append(";");
//					buffer.append("price = ").append(detail.price).append(";");
//					buffer.append("price_amount = ").append(detail.price_amount).append(";");
//					buffer.append("price_currency_code = ").append(detail.price_currency_code).append(";");
//					buffer.append("title = ").append(detail.title).append(";");
//					buffer.append("description = ").append(detail.description).append(";")
//					.append("\n");;
//					Log.i("CppHelper", "buffer = " + buffer.toString());
				}
//				System.out.print(buffer.toString());
			}
			else
			{
				System.out.print("query error");
			}
			}

			});

}
	
	public void showProgressDialog() {
        if (mProgressDialog == null) {
            mProgressDialog = new ProgressDialog(AppActivity.this);
            mProgressDialog.setIndeterminate(true);
            mProgressDialog.setMessage("Loading.....");
        }
        if (!mProgressDialog.isShowing()) {
            mProgressDialog.show();
        }
    }

    public void dismissProgressDialog() {
        if (mProgressDialog != null && mProgressDialog.isShowing()) {
            mProgressDialog.dismiss();
        }
    }
	
	
	public void onResume() {
		
    	super.onResume();
    }
    
    public void onPause() {
    	
    	super.onPause();
    	
    }
    protected void onDestroy() {
    	Commplatform.getInstance().destroy();
    	super.onDestroy();
    }
    static {
        System.loadLibrary("cocos2dcpp");
    }
}
