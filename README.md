Cocos2d-x + Nend Icon サンプルゲーム
---------------------------------

別名:The 数当て for iOS/Android

Maxi Gundan H.Ishida

ゲーム仕様
-----------------------
・タイトル画面  
"Play"を押すとゲームが始まります  

・ゲーム画面  
下に1~5の数字ボタンがありますので、  
カンで当ててください。  

無事当たると終了画面に遷移します  

・終了画面  
何回目で当たったか　と　評価　を表示します。  
この段階で初めて、上部に４つNendアイコン広告を表示します。  

ソースコードの変更でアイコンは最大６つまで対応。  
(ただし、NendのテストIDだと５つしか表示されない)  
ゲーム画面にレイヤーをかぶせているだけです。  



事前準備(iOS/Android共通)
-----------------------
iOSはXcode5  
Androidは最新か新しめのEclipse + Android SDK + Android NDK  
がインストール済みで、一通りビルドできる環境にある事が前提。  

## 1. cocos2d-x-2.2.xをDL
http://www.cocos2d-x.org/download  

## 2. Nend SDK 2.3.xをDL
http://nend.net  
(事前にNendに登録しておく事)  

## 3. このソースコードをDL
gitがよくわからない場合はページ右側メニューののZIP Downloadからzipでどうぞ  


作成するアプリ名は"TestGameNendIconAd"、パッケージは"com.MyCompany.TestApp"  
フォルダは"~/cocos2d-x-2.2.2/"としています。  
各自、自分の環境のパスに読み替えてください。  

## 4. ターミナル起動、プロジェクト作成
    cd ~/cocos2d-x-2.2.2/tools/project-creator/
    python create_project.py -project TestGameNendIconAd -package com.MyCompany.TestApp -language cpp
⇒正常に各プラットフォーム全部Done!が表示されればOK  
(失敗する場合は大抵パーミッション周りかパス関連)  


ビルド手順(iOS)
------------
## 1. プロジェクト作成
事前準備4で済んでいる。  

## 2. iOSのプロジェクトを実行、XCode起動
Finderから、ホーム以下  
cocos2d-x-2.2.2/projects/TestGameNendIconAd/ というフォルダができている。  
その中に色々なプラットフォームのプロジェクトができているので、  
proj.iosフォルダ内から、TestGameNendIconAd.xcodeprojを実行  

## 3. プロジェクトにNend SDKライブラリ追加
Finderから、  
~/NendSDK_iOS-2.3.1/Nend/NendAd/  
をフォルダごとドラッグ＆ドロップ  

## 4. 必要なframework追加
Target-Build Phases-Link Binary With Librariesから、

    Security.framework
    AdSupport.framework
の２つを追加。  
この辺りは、Cocos2d-xとNend SDKのバージョンによって変わりうる。  

## 5. ソースコード追加
    Classes/
    proj.ios/
    Resources/
のもの。一部上書きあり。Finderで間違えて「フォルダ置き換え」してしまわないように。  

## 6. ソースコードを、環境内に登録
以下のものが無いと思うので、ドラッグ＆ドロップして環境に追加する。Copyは作らない。
 
    Classes/GameScene.cpp
    Classes/GameScene.h
    Classes/TitleScene.cpp
    Classes/TitleScene.h
    proj.ios/IconAdManager.h
    proj.ios/IconAdManager.mm
    proj.ios/IconAdManagerC.h
    Resouces/atari.png
    Resouces/hazure.png
    Resouces/title.png

## 7. 回転方向を設定
このゲームは、縦方向タイプなので、Xcodeのターゲット設定から、  
Supported Interface Orientationsから、Portraitのみに設定をしておく。  

また、RootViewController.mm の以下の行をPortraitに変更

    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
        ↓  

    return UIInterfaceOrientationIsPortrait( interfaceOrientation );

## 8. ビルド実行
Runを押してビルド。  
lcurlとかlwebsocketsでリンクエラーが出る場合は、  
たぶんもともとcocos2d-xのパスが違っているので、  
cocos2d-xの環境内からXcodeにドラッグ&ドロップで解決できる。  

    cocos2d-x-2.2.2/cocos2dx/platform/third_party/ios/libraries/libcurl.a
    cocos2d-x-2.2.2/external/libwebsockets/ios/lib/libwebsockets.a
とか  

ビルド手順(Android)
-----------------
初めてcocos2d-xを使う場合は、  
Eclipseで、"libcocos2dx"のインポート、ビルドして"libcocos2dx.jar"作成しておく。  
また、EclipseからNativeビルドするのに、  
"NDK_ROOT"と"COCOS2DX_ROOT"の環境変数をセットしておくとできるらしい。  
ADT-環境設定を開く　C/C++ - Build - Environment から  
Name:NDK_ROOT  
Value:/Applications/android-ndk-r9c  
Name:COCOS2DX_ROOT  
Value:/Users/MaxiGundan/cocos2d-x-2.2.2  
これで、Eclipseからcocos2d-xのNativeビルドができるらしい。（未確認）  

## 1. プロジェクト作成
事前準備4で済んでいる。  

## 2. ソースコード上書き
    Classes/
    proj.android/
    Resources/
のもの。一部上書きあり。Finderで間違えて「フォルダ置き換え」してしまわないように。  
(Android.mkも変更しています)  

## 3. Nend SDKライブラリのコピー
proj.androidフォルダに"libs"というフォルダを作成し、  
Nend SDKの環境内にある、nendSDK-2.3.2.jar ファイルを  
proj.android/libs フォルダにコピーする。  

## 4. Native(cpp)のビルド
Eclipse用のプロジェクトに組み込まれているので  
Eclipseからできるみたいだけどよく分からないので手動で行った。  

手動で./build_native.shを実行
    cd ~/cocos2d-x-2.2.2/projects/TestGameNendIconAd/proj.android
    ./build_native.sh

ビルドが走るのでしばらく待つ。  

エラーが発生せず、
    Install        : libcocos2dcpp.so => libs/armeabi/libcocos2dcpp.so
    make: Leaving directory(略
まで終わっていればNative側は正常終了している。  

## 5. Eclipse起動、環境インポート(最初の１回のみ必要)
メニューのFile-Import選択、General-Existing Projects into Workspaceで  
Select root directoryのBrowseボタンから、  
~/cocos2d-x-2.2.2/projects/TestGameNendIconAd/proj.android のフォルダを指定。  
自動的にTestGameNendIconAdプロジェクト環境が認識されるので、Finish押すと環境が読み込まれる。  

## 6. Android Manifestの変更
表示方向は縦方向なので、"android:screenOrientation"を"portrait"に。

    android:screenOrientation="portrait"

広告表示用のパーミッション登録  
以下の2つが必要  

    <uses-permission android:name="android.permission.INTERNET"/>
    <uses-permission android:name="android.permission.ACCESS_NETWORK_STATE"/>

## 7. 広告表示用のActivityをセットする
"IconAdMgr"という広告表示用のstatic Classを作ってあるので、  
そこにActivity登録する事で、Nativeから広告制御できるようになっている。  

TestGameNendIconAd.java の冒頭に追加

    public class TestGameNendIconAd extends Cocos2dxActivity{
        protected void onCreate(Bundle savedInstanceState){
            super.onCreate(savedInstanceState);	
            IconAdMgr.setActivity(this);  // IconAd呼び出し用Activity登録
        }


## 8. ビルド設定
./build_native.sh を手動で行っているので、  
Propatires - Builders から "CDT Builder"を外しておく。  

また、IconAdMgr.javaの中で、以下の判定を行っているので、  
Project Build Targetは3.0(Honeycomb)以降にする。  

    if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB)

ただ、このコードは、  
Honeycomb以降なら無理矢理IconViewを小さくすることもできますよー というサンプルなので  
それより前のバージョンの端末にも対応したいとか、要らない場合は削除してもいいです。  

## 9. ビルド
Project - Build Project 実行  
ここの時点でエラーが出ていれば、C++のコードが何かおかしい。⇒ cpp側のビルド設定を見直す  
これ以降でエラーが出ていれば、Java側で何かおかしい。  

## 8. 実行
Run Application でうまく動けばOK  
  

  
以上です  

  
  
非常に我流ですので、  
もしここはこうした方がいいよーとか、  
ここは間違ってるよーとかがございましたら、  
メール(Maxi.Corpsあっとじーめーるどっとこむ)か、twitterにて連絡いただけるとうれしいです。  
  
  

  

  

  

  
DLだけして帰るん？（´・ω・`）  
↓いつでもフォローしてくれていいねんで？  
twitter: https://twitter.com/MaxiGundan  
blog:http://maxigundan.hatenablog.jp  