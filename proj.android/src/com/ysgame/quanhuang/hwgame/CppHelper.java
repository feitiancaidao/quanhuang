package com.ysgame.quanhuang.hwgame;

import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.content.DialogInterface;


public class CppHelper {
	

	public native static void payResultC(boolean isSuccess,String payid);
	public native static void exitGame();
	
	public static void payRequest(String payid)
	{
		String orderid= chagePayidtoOrderid(payid);
		
		AppActivity.main.pay(orderid);
	}
	
	public static void close(){
		AppActivity.main.closeGame();
	}
	
	public static void BackBtn()
	{
		AppActivity.main.runOnUiThread(new Runnable(){

			@Override
			public void run() {
				// TODO Auto-generated method stub
				Builder dialog=new AlertDialog.Builder(AppActivity.main.getContext())
				.setTitle("EXIT")
				.setPositiveButton("OK", new DialogInterface.OnClickListener() {
					
					@Override
					public void onClick(DialogInterface dialog, int which) {
						// TODO Auto-generated method stub
						exit();
					}
				})
				.setNegativeButton("CANCEL", 
						new DialogInterface.OnClickListener() {
							
							@Override
							public void onClick(DialogInterface dialog, int which) {
								// TODO Auto-generated method stub
								
							}
						});
				dialog.show();	
			}
		});
	}
	
	public static void exit()
	{
		AppActivity.main.closeGame();
	}
	
	
	static String chagePayidtoOrderid(String payid)
	{
		String orderid=new String();
		
		if(Payid.BUY_Bazhinv.getid().compareTo(payid)==0)
			orderid="1";
		if(Payid.BUY_Bajiubei.getid().compareTo(payid)==0)
			orderid="2";
		if(Payid.BUY_Shoushen.getid().compareTo(payid)==0)
			orderid="3";
		if(Payid.BUY_JinjiDuobi.getid().compareTo(payid)==0)
			orderid="4";
		if(Payid.BUY_Money1888.getid().compareTo(payid)==0)
			orderid="5";
		if(Payid.BUY_Money18888.getid().compareTo(payid)==0)
			orderid="6";
		if(Payid.BUY_Fuhuo.getid().compareTo(payid)==0)
			orderid="7";
		if(Payid.BUY_Nuqi.getid().compareTo(payid)==0)
			orderid="8";
		
		
		return orderid;
	}
	
	static String changeOrderidtoPayid(String orderid)
	{
		String payid=null;
		
		if(orderid.compareTo("1")==0)
			payid=Payid.BUY_Bazhinv.getid();
		if(orderid.compareTo("2")==0)
			payid=Payid.BUY_Bajiubei.getid();
		if(orderid.compareTo("3")==0)
			payid=Payid.BUY_Shoushen.getid();
		if(orderid.compareTo("4")==0)
			payid=Payid.BUY_JinjiDuobi.getid();
		if(orderid.compareTo("5")==0)
			payid=Payid.BUY_Money1888.getid();
		if(orderid.compareTo("6")==0)
			payid=Payid.BUY_Money18888.getid();
		if(orderid.compareTo("7")==0)
			payid=Payid.BUY_Fuhuo.getid();
		if(orderid.compareTo("8")==0)
			payid=Payid.BUY_Nuqi.getid();
		
		return payid;
	}
	
	static void payResult(boolean isSuccess, String orderid)
	{
		String payid=null;
		payid=changeOrderidtoPayid(orderid);
		payResultC(isSuccess,payid);
	}
	
	
}




enum Payid{
	
	 BUY_Bazhinv("8"), BUY_Bajiubei("9"),BUY_JinjiDuobi("23"),BUY_Shoushen("24"), 
			BUY_Money1888("25"),BUY_Money5888("26"),BUY_Money18888("27"),BUY_Fuhuo("10"),BUY_Nuqi("34"), 
			BUY_Jihuolayer("19"),BUY_Dalibao("16");
	
private final String payid;
private Payid(String id)
{
	payid=id;
}
public String getid(){ return payid;}
}

