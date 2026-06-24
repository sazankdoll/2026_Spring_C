#include <DxLib.h>
#include "../Application.h"
#include "Resource.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::instance_ = nullptr;

void ResourceManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new ResourceManager();
	}
	instance_->Init();
}

ResourceManager& ResourceManager::GetInstance(void)
{
	return *instance_;
}

void ResourceManager::Init(void)
{

	// 推奨しませんが、どうしても使いたい方は
	using RES = Resource;
	using RES_T = RES::TYPE;
	static std::string PATH_IMG = Application::PATH_IMAGE;
	static std::string PATH_MDL = Application::PATH_MODEL;
	static std::string PATH_EFF = Application::PATH_EFFECT;
	static std::string PATH_SND = Application::PATH_SOUND;

	Resource* res;
	//モデル
	res = new RES(RES_T::MODEL, PATH_MDL + "Player/PlayerY.mv1");
	resourcesMap_.emplace(SRC::PLAYERY, res);
	res = new RES(RES_T::MODEL, PATH_MDL + "Player/PlayerB.mv1");
	resourcesMap_.emplace(SRC::PLAYERB, res);
	res = new RES(RES_T::MODEL, PATH_MDL + "Stage/Stage.mv1");
	resourcesMap_.emplace(SRC::MAIN_STAGE, res);
	res = new RES(RES_T::MODEL, PATH_MDL + "SkyDome/SkyDome.mv1");
	resourcesMap_.emplace(SRC::SKY_DOME, res);
	//画像
	res = new RES(RES_T::IMG, PATH_IMG + "hosizora.png");
	resourcesMap_.emplace(SRC::TITLE_IMG, res);
	res= new RES(RES_T::IMG, PATH_IMG + "AttackImg.png");
	resourcesMap_.emplace(SRC::ATTACK_IMG, res);
	res= new RES(RES_T::IMG, PATH_IMG + "RadiusImg.png");
	resourcesMap_.emplace(SRC::RADIUS_IMG, res);
	res= new RES(RES_T::IMG, PATH_IMG + "RangeImg.png");
	resourcesMap_.emplace(SRC::RANGE_IMG, res);
	res= new RES(RES_T::IMG, PATH_IMG + "SpeedImg.png");
	resourcesMap_.emplace(SRC::SPEED_IMG, res);

	//サウンド
	//BGM
	res = new RES(RES_T::SOUND, PATH_SND + "Bgm/title.mp3");
	resourcesMap_.emplace(SRC::TITLE_BGM, res);
	res = new RES(RES_T::SOUND, PATH_SND + "Bgm/AS_1055033_宇宙映像、ゲーム＿バトルシーン.mp3");
	resourcesMap_.emplace(SRC::GAME_BGM, res);
	res = new RES(RES_T::SOUND, PATH_SND + "Bgm/rizaruto.mp3");
	resourcesMap_.emplace(SRC::RESULT_BGM, res);

	//SE
	res = new RES(RES_T::SOUND, PATH_SND + "Se/AS_151665_ダメージ音2.mp3");
	resourcesMap_.emplace(SRC::HIT_SE, res);
	res = new RES(RES_T::SOUND, PATH_SND + "Se/AS_476033_レーザービームが射出される音.mp3");
	resourcesMap_.emplace(SRC::WEPON_SE, res);
	res = new RES(RES_T::SOUND, PATH_SND + "Se/AS_1074147_ドカーン！（爆発音、衝撃、爆弾）_2.mp3");
	resourcesMap_.emplace(SRC::CRASH_SE, res);
	res = new RES(RES_T::SOUND, PATH_SND + "Se/AS_1515947_アイテムを手に入れた音3.mp3");
	resourcesMap_.emplace(SRC::GET_ITEM_SE, res);

}

void ResourceManager::Release(void)
{
	for (auto& p : loadedMap_)
	{
		p.second.Release();
	}

	loadedMap_.clear();
}

void ResourceManager::Destroy(void)
{
	Release();
	for (auto& res : resourcesMap_)
	{
		res.second->Release();
		delete res.second;
	}
	resourcesMap_.clear();
	delete instance_;
}

const Resource& ResourceManager::Load(SRC src)
{
	const Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return dummy_;
	}
	return res;
}

int ResourceManager::LoadModelDuplicate(SRC src)
{
	Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return -1;
	}

	int duId = MV1DuplicateModel(res.handleId_);
	res.duplicateModelIds_.push_back(duId);

	return duId;
}

ResourceManager::ResourceManager(void)
{
}

Resource& ResourceManager::_Load(SRC src)
{

	// ロード済みチェック
	const auto& lPair = loadedMap_.find(src);
	if (lPair != loadedMap_.end())
	{
		return *resourcesMap_.find(src)->second;
	}

	// リソース登録チェック
	const auto& rPair = resourcesMap_.find(src);
	if (rPair == resourcesMap_.end())
	{
		// 登録されていない
		return dummy_;
	}

	// ロード処理
	rPair->second->Load();

	// 念のためコピーコンストラクタ
	loadedMap_.emplace(src, *rPair->second);

	return *rPair->second;

}
