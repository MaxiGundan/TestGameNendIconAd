//
//  IconAd.mm
//  TestIconAd
//
//  Created by MaxiGundan H.Ishida.
//
//

#import "IconAdManager.h"
#import "AppController.h"

@interface IconAdManager ()

@end

@implementation IconAdManager
- (id)init {
	[super init];
    
    nadIconLoader = nil;
    nadIconViewArray = nil;
	return self;
}

-(void)createView:(UIView*)rootView yPos:(float)yPos
{
    if (nadIconLoader!=nil) {
        return;
    }
    nadIconLoader = [[NADIconLoader alloc] init];
    nadIconViewArray = [[NSMutableArray alloc] init];
#ifdef DEBUG_PRINT
    nadIconLoader.isOutputLog = YES;
#endif
    
    //ウィンドウ幅取得
    CGRect screenRect = [[UIScreen mainScreen] bounds];
    const CGFloat windowWidth = screenRect.size.width;

	const CGFloat iconWid = ICNAD_WIDTH;
	const CGFloat iconHei = ICNAD_HEIGHT;

    //表示させる幅をウィンドウ幅全般に均等割り当てするための、マージン＆オフセット計算
    //図 → [(a)■(b)■(b)■(b)■ ] ■:アイコン (a):offset (b):margin []:ウィンドウサイズ全域とする
    //(任意幅・任意の場所に表示したい時はこのあたりの数値を引数にして上位からセットする等)
    const CGFloat offset = ((windowWidth/ICNAD_NUMS)-iconWid)/2;
    const CGFloat margin = (windowWidth/ICNAD_NUMS) - iconWid;
    
    //アイコンの表示位置を、一つずつセット
	for (int i=0; i < ICNAD_NUMS; i++)
	{
		CGRect iconFrame;
		iconFrame.origin = CGPointMake(offset+(iconWid+margin)*i, yPos);
		iconFrame.size = CGSizeMake(iconWid, iconHei);
		NADIconView* iconView = [[NADIconView alloc]initWithFrame:iconFrame];
        
        if (!(ICNAD_SHOW_TITLE)) {
            iconView.textHidden = YES;
        }else{
            iconView.textHidden = NO;
        }
        if (ICNAD_SPACE) {
            iconView.iconSpaceEnabled = YES;
        }else{
            iconView.iconSpaceEnabled = NO;
        }
        iconView.tag = i;
        [iconView setTextColor:[UIColor whiteColor]];   //文字色設定
        
		[nadIconLoader addIconView:iconView];
        [nadIconViewArray addObject:iconView];
		[rootView addSubview:iconView];
		[iconView release];
	}

    //loaderへの設定
    [nadIconLoader setNendID:kNEND_ID spotID:kSPOT_ID];
    [nadIconLoader setDelegate:self];
    
    //開始
    [nadIconLoader load];
}

-(void)locateView:(float)yPos
{
    if (nadIconViewArray==nil) {
        return;
    }
    
    int itemsize = [nadIconViewArray count];
    //アイコンの表示位置を、一つずつ再設定
    for (int i=0; i < itemsize; i++)
    {
        //保存されているNADIconView取り出し
        NADIconView* iconView = (NADIconView*)[nadIconViewArray objectAtIndex:i];
        CGRect iconFrame;
		iconFrame.origin = CGPointMake(iconView.frame.origin.x, yPos);
		iconFrame.size = iconView.frame.size;
        
        [iconView setFrame:iconFrame];
    }
}

-(void)releaseView
{
    if (nadIconLoader==nil) {
        return;
    }
    
    int itemsize = [nadIconViewArray count];
    //ここでアイコン一個ずつ明示削除しておく
    //(SDK任せで一気にやっても良いけど広告受信とかレジューム処理とかタッチ処理とかGCとか絡むと
    //排他タイミングシビアなので各社不具合出やすいように思えるので念のため←憶測)
    for (int i=0; i < itemsize; i++) {
        NADIconView* iconCell = (NADIconView*)[nadIconViewArray objectAtIndex:i];
        [nadIconLoader removeIconView:iconCell];
        [iconCell removeFromSuperview];
    }
    
    [nadIconLoader setDelegate:nil];
    nadIconLoader = nil;
    if (itemsize>0) {
        [nadIconViewArray removeAllObjects];
    }
    nadIconViewArray = nil;
}

-(void)resumeView
{
    if (nadIconLoader==nil) {
        return;
    }
    [nadIconLoader resume];
}
-(void)pauseView
{
    if (nadIconLoader==nil) {
        return;
    }
    [nadIconLoader pause];
}
-(void)refreshView
{
    if (nadIconLoader==nil) {
        return;
    }
    [nadIconLoader load];    //loadで代用可
}


// ------------------------------------------------------------------------------------------------
// 受信状況の通知
// ------------------------------------------------------------------------------------------------

#pragma mark - NADIconLoaderDelegate
// 広告の受信に成功し表示できた場合に１度通知される任意メソッドです。
-(void)nadIconLoaderDidFinishLoad:(NADIconLoader *)iconLoader{
#ifdef DEBUG_PRINT
    NSLog(@"NADIconViewDelegate nadIconLoaderDidFinishLoad");
#endif
    //cpp側へ流す
    if (pDelegateFunc!=NULL) {
        //登録されているなら関数実行
        pDelegateFunc();
    }
}

// 以下は広告受信成功ごとに通知される任意メソッドです。
-(void)nadIconLoaderDidReceiveAd:(NADIconLoader *)iconLoader nadIconView:(NADIconView *)nadIconView{
#ifdef DEBUG_PRINT
    NSLog(@"NADIconViewDelegate nadIconLoaderDidReceiveAd, nadIconView.tag = %d", nadIconView.tag);
#endif
}

// 以下は広告受信失敗ごとに通知される任意メソッドです。
-(void)nadIconLoaderDidFailToReceiveAd:(NADIconLoader *)iconLoader nadIconView:(NADIconView *)nadIconView{
#ifdef DEBUG_PRINT
    if (nadIconView) {
        NSLog(@"NADIconViewDelegate nadIconLoaderDidFailToReceiveAd, nadIconView.tag = %d", nadIconView.tag);
    }
    else{
        NSLog(@"NADIconViewDelegate nadIconLoaderDidFailToReceiveAd");
    }
    
    // エラー発生時の情報をログに出力します
    NSError* nadError = iconLoader.error;
    // エラーコード
    NSLog(@"code = %ld", (long)nadError.code);
    // エラーメッセージ
    NSLog(@"message = %@", nadError.domain);
#endif

}

// 以下はバナー広告がクリックされるごとに通知される任意メソッドです。
-(void)nadIconLoaderDidClickAd:(NADIconLoader *)iconLoader nadIconView:(NADIconView *)nadIconView{
#ifdef DEBUG_PRINT
    NSLog(@"NADIconViewDelegate nadIconLoaderDidClickAd, nadIconView.tag = %d", nadIconView.tag);
#endif
}


// ------ C codes -------

static IconAdManager *iconAdMgr = nil;  //Singleton
static void (*pDelegateFunc)(void) = NULL;

void IconAdCreateView(float yPos)
{
    if (iconAdMgr!=nil) {
        return;
    }
    UIView *rootView = [UIApplication sharedApplication].keyWindow.rootViewController.view;
    iconAdMgr = [[IconAdManager alloc] init];
    [iconAdMgr createView:rootView yPos:yPos];
}

void IconAdLocateView(float yPos)
{
    if (iconAdMgr!=nil) {
        [iconAdMgr locateView:yPos];
    }
}

void IconAdReleaseView(void)
{
    if (iconAdMgr==nil) {
        return;
    }
    [iconAdMgr releaseView];
    iconAdMgr = nil;
}

void IconAdPauseView(void)
{
    if (iconAdMgr!=nil) {
        [iconAdMgr pauseView];
    }
}
void IconAdResumeView(void)
{
    if (iconAdMgr!=nil) {
        [iconAdMgr resumeView];
    }
}
void IconAdRefreshView(void)
{
    if (iconAdMgr!=nil) {
        [iconAdMgr refreshView];
    }
}
void registerFunctionPointer(void (*pFunc)(void))
{
    pDelegateFunc = pFunc;
}
void clearFunctionPointer(void)
{
    pDelegateFunc = NULL;
}



@end
