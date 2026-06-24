#pragma once
class Timer
{
public:

    // ミリ秒変換
    static constexpr int CHANGE_MR = 1000;

	//60秒変換
	static constexpr int CHANGE_S = 60;

    // タイマー最小値
	static constexpr int MIN_TIME = 3;

    // コンストラクタ
    Timer();
    // デストラクタ
    ~Timer();
    // イニット
    void Init();
    // 更新
    void Update();
    // 描画
    void Draw();
    // 時間取得 (タイマー開始)
    void Start(float time);
    //タイマーの再開
    void ReStart();

    // 時間停止 (isPlay_をfalseにする)
    void Stop();
    // 時間リセット
    void Reset();

    // 時間倍率を設定 (1.0で通常、0.5でスロー、0.0で一時停止)
    void SetTimeScale(double scale);
    // 時間倍率を取得
    double GetTimeScale() const;

    // 現在の残り時間の分を取得
    int GetMin() const;
    // 現在の残り時間の秒を取得
    int GetSec() const;

private:
    // ゲーム内で経過すべき残り時間 (ミリ秒)
    int RemainingTime_;

    // 前回 Update 時に記録したシステム時刻 (GetNowCount() の値)
    int LastSystemTime_;

    // タイマーが作動中か
    bool isPlay_;

    // 時間の流れの倍率 (1.0が通常)
    double TimeScale_;

    // 表示用の分と秒
    int min_;
    int sec_;
};