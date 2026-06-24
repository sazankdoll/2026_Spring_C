#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "Manager/InputManager.h"
#include "Manager/ResourceManager.h"
#include "Manager/SceneManager.h"
#include "Manager/SoundManager.h"
#include "FpsController/FpsController.h"
#include "Application.h"

Application* Application::instance_ = nullptr;

// データパス
const std::string Application::PATH_IMAGE = "Data/Image/";
const std::string Application::PATH_MODEL = "Data/Model/";
const std::string Application::PATH_EFFECT = "Data/Effect/";
const std::string Application::PATH_SOUND = "Data/Sound/";
const std::string Application::PATH_CSV = "Data/Csv/";

void Application::CreateInstance(void)
{
	//インスタンス生成
	if (instance_ == nullptr)
	{
		instance_ = new Application();
	}
	instance_->Init();
}

Application& Application::GetInstance(void)
{
	return *instance_;
}

void Application::Init(void)
{

	// アプリケーションの初期設定
	SetWindowText("光体バトル");

	// ウィンドウサイズ
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, COLOR_DEPTH);
	ChangeWindowMode(true);
	// FPS制御初期化
	fpsController_ = new FpsController(FRAME_RATE);
	// DxLibの初期化
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	isInitFail_ = false;
	if (DxLib_Init() == -1)
	{
		isInitFail_ = true;
		return;
	}

	// Effekseerの初期化
	InitEffekseer();

	// 乱数のシード値を設定する
	DATEDATA date;

	// 現在時刻を取得する
	GetDateTime(&date);

	// 乱数の初期値を設定する
	// 設定する数値によって、ランダムの出方が変わる
	SRand(date.Year + date.Mon + date.Day + date.Hour + date.Min + date.Sec);

	// 入力制御初期化
	SetUseDirectInputFlag(true);
	InputManager::CreateInstance();

	// リソース管理初期化
	ResourceManager::CreateInstance();

	// シーン管理初期化
	SceneManager::CreateInstance();
	SoundManager::CreateInstance();
}

void Application::Run(void)
{
	// 入力管理のインスタンスを取得
	InputManager& inputManager = InputManager::GetInstance();
	// シーン管理のインスタンスを取得
	SceneManager& sceneManager = SceneManager::GetInstance();

	// ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// 入力の更新
		inputManager.Update();
		// シーンの更新
		sceneManager.Update();
		// シーンの描画
		sceneManager.Draw();

		ScreenFlip();

		// 理想FPS経過待ち
		fpsController_->Wait();
	}

}

void Application::Destroy(void)
{
	// 入力管理解放
	InputManager::GetInstance().Destroy();
	// リソース管理解放
	ResourceManager::GetInstance().Destroy();
	// シーン管理解放
	SceneManager::GetInstance().Destroy();

	// Effekseerを終了する。
	Effkseer_End();

	// DxLib終了
	if (DxLib_End() == -1)
	{
		isReleaseFail_ = true;
	}

	// FPSコントローラーの解放
	delete fpsController_;
	// インスタンスのメモリ解放
	delete instance_;

}

bool Application::IsInitFail(void) const
{
	return isInitFail_;
}

bool Application::IsReleaseFail(void) const
{
	return isReleaseFail_;
}

Application::Application(void)
	:
	isInitFail_(false),
	isReleaseFail_(false)
{
	fpsController_ = nullptr;
}

void Application::InitEffekseer(void)
{
	// エフェクシア初期化の初期化
	if (Effekseer_Init(PARTICLE_MAX) == -1)
	{
		DxLib_End();
	}

	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
}
