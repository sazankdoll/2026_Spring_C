#include <string>
#include <DxLib.h>

#include "../../Application.h" // 外部ファイルはコメントアウト
// #include "../../Utility/AsoUtility.h" // 外部ファイルはコメントアウト

#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::Init()
{
    RemainingTime_ = 0;
    LastSystemTime_ = 0;
    isPlay_ = false;
    TimeScale_ = 1.0; // デフォルトは通常速度
    min_ = MIN_TIME;
    sec_ = 0;
}

void Timer::Update()
{
    // 停止中、またはタイマー未開始なら何もしない
    if (!isPlay_ || RemainingTime_ <= 0)
    {
        // 停止中は LastSystemTime_ を更新しないことで、再開時に正確な差分が取れる
        return;
    }

    // 1. 現在のシステム時刻を取得
    int CurrentSystemTime = GetNowCount();

    // 2. 前フレームからの実経過時間を計算
    int RealElapsedTime = CurrentSystemTime - LastSystemTime_;

    // 3. TimeScaleを適用して、ゲーム内での論理的な経過時間を計算
    // TimeScaleが0.0なら ElapsedTime は 0 になり、一時停止となる
    // TimeScaleが0.5なら ElapsedTime は半分の速度となり、スローとなる
    int LogicalElapsedTime = (int)(RealElapsedTime * TimeScale_);

    // 4. 残り時間を減算
    RemainingTime_ -= LogicalElapsedTime;

    // 5. 次のフレームのために現在のシステム時刻を保存
    LastSystemTime_ = CurrentSystemTime;

    // 6. タイマー終了判定と表示更新
    if (RemainingTime_ <= 0)
    {
        // タイマーが0になったら停止
        RemainingTime_ = 0;
        Stop();
        min_ = 0;
        sec_ = 0;
    }
    else
    {
        // 表示用の分と秒を更新
        min_ = RemainingTime_ / (CHANGE_MR * CHANGE_S);
        sec_ = (RemainingTime_ / CHANGE_MR) % CHANGE_S;
    }
}

void Timer::Draw()
{
}

void Timer::Start(float time)
{
    // 指定された時間をミリ秒に変換して残り時間にセット
    RemainingTime_ = (int)(time * CHANGE_MR);

    // 現在のシステム時刻を記録し、計測を開始
    LastSystemTime_ = GetNowCount();
    isPlay_ = true;

    // TimeScaleをリセット
    TimeScale_ = 1.0;
}

void Timer::ReStart()
{
    if (RemainingTime_ > 0 && !isPlay_)
    {
		// 停止中で残り時間がある場合に再開
		LastSystemTime_ = GetNowCount();
		isPlay_ = true;
	}
}

void Timer::Stop()
{
    // isPlay_をfalseにするだけで、残り時間やTimeScaleは保持される
    isPlay_ = false;
}

void Timer::Reset()
{
    RemainingTime_ = 0;
    LastSystemTime_ = 0;
    isPlay_ = false;
    TimeScale_ = 1.0;
    min_ = 0;
    sec_ = 0;
}

void Timer::SetTimeScale(double scale)
{
    // 時間倍率は 0.0 以上に制限
    if (scale >= 0.0)
    {
        TimeScale_ = scale;
    }
}

double Timer::GetTimeScale() const
{
    return TimeScale_;
}

int Timer::GetMin() const
{
    return min_;
}

int Timer::GetSec() const
{
    return sec_;
}