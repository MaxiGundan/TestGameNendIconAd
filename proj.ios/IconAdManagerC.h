//
//  IconAdManagerC.h
//  TestIconAd
//
//  Created by MaxiGundan H.Ishida.
//
//  cppから呼び出し用外部公開C関数定義
//

#ifndef __TestIconAd__IconAdManagerC__
#define __TestIconAd__IconAdManagerC__

//画面外座標
#define ICNAD_POS_INVALID (-1000)

//アイコン広告作成・表示
// yPos   :表示位置y座標(UIView座標系 注：Cocos2dとy軸が上下逆)
void IconAdCreateView(float yPos);

//アイコン広告位置変更
// yPos   :表示位置y座標(UIView座標系 注：Cocos2dとy軸が上下逆)
void IconAdLocateView(float yPos);

//アイコン広告解放
void IconAdReleaseView(void);

//表示ポーズ
void IconAdPauseView(void);
//表示レジューム
void IconAdResumeView(void);
//表示更新
void IconAdRefreshView(void);


//Delegate Method実行用
// pFunc :DelegateMethod飛ばし先関数ポインタ
// 強引だけどたぶんNADIconLoaderDelegateメソッドをCコードへ流せるはず(未確認)
void registerFunctionPointer(void (*pFunc)(void));
void clearFunctionPointer(void);


#endif /* defined(__TestIconAd__IconAdManagerC__) */
