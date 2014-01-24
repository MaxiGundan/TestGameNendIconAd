//
//  IconAdManager.h
//  TestIconAd
//
//  Created by MaxiGundan H.Ishida.
//
//

#import <Foundation/Foundation.h>
#import "NADIconLoader.h"
#import "IconAdManagerC.h"

//Nend ID (各自のIDに変更すること)
#define kNEND_ID 	@"2349edefe7c2742dfb9f434de23bc3c7ca55ad22"  //Nend test apiKey
#define kSPOT_ID 	@"101281"  //Nend test SpotID

//アイコン設定
//#define ICNAD_SET_NUM6
#if defined(ICNAD_SET_NUM6)
 //６つ表示設定
 #define ICNAD_NUMS   (6)           //アイコン個数
 #define ICNAD_SPACE    (FALSE)     //アイコン余白あり
 #define ICNAD_WIDTH    (50)        //アイコン幅
 #define ICNAD_HEIGHT   (50)        //アイコン高さ
 #define ICNAD_SHOW_TITLE (FALSE)   //タイトル表示
#else
//デフォルト設定
 #define ICNAD_NUMS     (4)         //アイコン個数
 #define ICNAD_SPACE    (TRUE)      //アイコン余白あり
 #define ICNAD_WIDTH    (75)        //アイコン幅
 #define ICNAD_HEIGHT   (75)        //アイコン高さ
 #define ICNAD_SHOW_TITLE (TRUE)    //タイトル表示
#endif

//デバッグ出力
#define DEBUG_PRINT


//Delegateを使いたいためにManagerを作る(Delegate見ない場合は不要)
@interface IconAdManager : NSObject<NADIconLoaderDelegate>{
    NADIconLoader* nadIconLoader;
    NSMutableArray* nadIconViewArray;
}
@end

