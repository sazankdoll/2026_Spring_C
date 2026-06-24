#pragma once


class Point
{
private:
	static Point* _instance;  // シングルトンインスタンス

	// 各プレイヤーのHP
	int php_;
	int pBhp_;
	

	// コンストラクタ（privateにして外部からのインスタンス化を防ぐ）
	Point(void);

public:
	// インスタンスの取得
	static Point* GetInstance();
	// デストラクタ
	~Point(void);

	// コピー・代入演算子を削除してシングルトンを保証
	Point(const Point&) = delete;
	Point& operator=(const Point&) = delete;

	void Init(void);

	//設定
	void SetpHp(int php);
	void SetpBhp(int pBhp);

	//取得
	int GetpHp(void);
	int GetpBhp(void);
	
};
