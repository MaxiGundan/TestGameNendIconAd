//
//  IconAdMgr.java
//
//  Created by MaxiGundan H.Ishida.
//
//  reference: http://albatrus.com/main/cocos2d/5379 (albatrusさんのNendアイコン表示方法)
//  reference: http://gaomar.blog.fc2.com/blog-entry-37.html (がおまるさんのレイアウト調整方法)
//
package com.MyCompany.NativeIF;

//Nend
import org.cocos2dx.lib.Cocos2dxActivity;

import net.nend.android.NendAdIconLayout;
import net.nend.android.NendAdIconLoader;
import net.nend.android.NendAdIconView;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.net.Uri;
import android.os.Build;
import android.util.Log;
import android.view.Display;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;

public class IconAdMgr {
	private static final boolean DEBUG_PRINT = true;
	private static final String TAG = "IconAdMgr";
	private static final int FP = RelativeLayout.LayoutParams.FILL_PARENT;
	private static final int WC = RelativeLayout.LayoutParams.WRAP_CONTENT;
	
	private static Activity mActivity = null;
	private static float mDensity = 1.0f;
	
	//Nend ID (各自のIDに変更すること)
	static final String ICON_API_KEY	= "0c734134519f25412ae9a9bff94783b81048ffbe";	//Nend test apikey
	static final int	ICON_SPOT_ID	= 101282;	//Nend test SpotID
	//Nend Ads
	private static RelativeLayout _iconAdLayout = null;	// Layout to display Ads (like NendAdIconLayout)
	private static NendAdIconLoader _iconAdLoader = null;
	
	//Ads Setting
	static final int NEND_ICON_NUMS	= 4;
	static final int NEND_DEFAULT_SIZE = 75;
	static boolean	ICNAD_SPACE;
	static int		ICNAD_WIDTH;
	static int		ICNAD_HEIGHT;
	static boolean	ICNAD_SHOW_TITLE;
	static NendAdIconView[] mIconViewArray;
	static float mIconDispWid;
	static float mIconOffset;
	static float mIconMargin;
	
	//Debug
	private static int DbgLogD(String tag, String msg){
		if(DEBUG_PRINT) {
			return Log.d(tag, msg);
		}
		return 0;
	}

	//initialize global icon params
    private static void initIconAdParameters()
    {
    	if(NEND_ICON_NUMS>4) {
    		ICNAD_SPACE = false;
    		ICNAD_WIDTH = 50;
    		ICNAD_HEIGHT = 50;
    		ICNAD_SHOW_TITLE = false;
    	}else{
    		ICNAD_SPACE = true;
    		ICNAD_WIDTH = 75;
    		ICNAD_HEIGHT = 75;
    		ICNAD_SHOW_TITLE = true;
    	}

    	//手動でIconViewを設定しておく
        //(細かい配置にこだわらなければ、絶対にNendAdIconLayer使った方が楽！
        // Nend SDK同梱サンプルソースやalbatrusさんのページが参考になります)
    	mIconViewArray = new NendAdIconView[NEND_ICON_NUMS];	//alloc array
    	for(int i=0; i<NEND_ICON_NUMS; i++) {
    		mIconViewArray[i] = new NendAdIconView(mActivity);	//initialize

    		mIconViewArray[i].setTitleColor(Color.WHITE);
    		mIconViewArray[i].setIconSpaceEnabled(ICNAD_SPACE);
    		mIconViewArray[i].setTitleVisible(ICNAD_SHOW_TITLE);
			if(NEND_ICON_NUMS>4) {
				if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB){
					//Honeycomb以降はsetScaleが使えるのでViewごと縮小する(それ以外は諦める)
					float scaleX = (float)ICNAD_WIDTH/(float)NEND_DEFAULT_SIZE;
					float scaleY = (float)ICNAD_HEIGHT/(float)NEND_DEFAULT_SIZE;
					mIconViewArray[i].setScaleX(scaleX);
					mIconViewArray[i].setScaleY(scaleY);
				}
			}
    	}

		// get resolution
    	WindowManager wm = (WindowManager) mActivity.getSystemService(Context.WINDOW_SERVICE);
    	Display disp = wm.getDefaultDisplay();
    	
    	// 手動で各アイコンのマージン計算する
    	mIconDispWid = ICNAD_WIDTH*mDensity;
        mIconOffset = ((float)(disp.getWidth()/NEND_ICON_NUMS)- mIconDispWid)/2;
        mIconMargin = (float)(disp.getWidth()/NEND_ICON_NUMS) - mIconDispWid;

        DbgLogD(TAG, "disp wid:"+(disp.getWidth())+" icon wid:"+mIconDispWid);
		DbgLogD(TAG, "offset:"+mIconOffset+" margin:"+mIconMargin);
    }
	
	// !!! ------- Register root activity ( Call This first ) ------- !!
	public static void setActivity(Activity activity) {
		mActivity = activity;
		mDensity = activity.getResources().getDisplayMetrics().density;
		DbgLogD(TAG, "mDensity:"+mDensity);

		_iconAdLayout = new RelativeLayout(mActivity);
		
		RelativeLayout.LayoutParams rootParams = new RelativeLayout.LayoutParams(FP, FP); 
		rootParams.addRule(RelativeLayout.ALIGN_PARENT_TOP);
		mActivity.addContentView(_iconAdLayout, rootParams);

		initIconAdParameters();
	}

	// ---------------- For Native Methods ---------------
	// C2dxのNativeから呼ばれるもの
    public static void createView(float yPos)
    {
    	if(_iconAdLoader!=null)
    		return;
    	
    	final float mYPos = yPos;
    	
		mActivity.runOnUiThread(new Runnable() {			
			@Override
			public void run() {
				DbgLogD(TAG, "createView:"+mYPos);
		    	
		    	
				_iconAdLoader = new NendAdIconLoader(mActivity, ICON_SPOT_ID, ICON_API_KEY);
				
				//一個一個追加していく
				for(int i=0; i<NEND_ICON_NUMS; i++) {
					//位置調整は手動
					NendAdIconView iconView = mIconViewArray[i]; //temp obj pointer
					RelativeLayout.LayoutParams iconParam = new RelativeLayout.LayoutParams(WC, WC);
					iconParam.setMargins((int)mIconOffset+(int)(mIconMargin+mIconDispWid)*i, (int)mYPos, 0, 0);
					iconView.setLayoutParams(iconParam);
					
		            _iconAdLayout.addView(iconView);

		            _iconAdLoader.addIconView(iconView);
				}
				_iconAdLoader.loadAd();
			}
		});
    }
    
    public static void locateView(float yPos)
    {
    	if(_iconAdLoader==null)
    		return;

    	final float mYPos = yPos;
		mActivity.runOnUiThread(new Runnable() {			
			@Override
			public void run() {
				DbgLogD(TAG, "locateView:"+mYPos);
				
				//一個一個変更
				for(int i=0; i<NEND_ICON_NUMS; i++) {
					NendAdIconView iconView = mIconViewArray[i]; //temp obj pointer
					RelativeLayout.LayoutParams iconParam = new RelativeLayout.LayoutParams(WC, WC);
					iconParam.setMargins((int)mIconOffset+(int)(mIconMargin+mIconDispWid)*i, (int)mYPos, 0, 0);
					iconView.setLayoutParams(iconParam);
				}
			}
		});
    }
    
    public static void releaseView()
    {
    	if(_iconAdLoader==null)
    		return;
    	
		mActivity.runOnUiThread(new Runnable() {			
			@Override
			public void run() {
				DbgLogD(TAG, "releaseView");
				//IconView解放
		    	_iconAdLayout.removeAllViews();
		    	
				_iconAdLoader.pause();
		    	_iconAdLoader = null;
			}
		});
    }
    
    public static void pauseView()
    {
    	if(_iconAdLoader==null)
    		return;

		mActivity.runOnUiThread(new Runnable() {			
			@Override
			public void run() {
				DbgLogD(TAG, "pauseView");
				_iconAdLoader.pause();
			}
		});
    }
    public static void resumeView()
    {
    	if(_iconAdLoader==null)
    		return;

		mActivity.runOnUiThread(new Runnable() {			
			@Override
			public void run() {
				DbgLogD(TAG, "resumeView");
				_iconAdLoader.resume();
			}
		});
    }
  
    public static void refreshView()
    {
    	if(_iconAdLoader==null)
    		return;

		mActivity.runOnUiThread(new Runnable() {			
			@Override
			public void run() {
				DbgLogD(TAG, "refreshView");
				_iconAdLoader.loadAd();
			}
		});
    }

}
