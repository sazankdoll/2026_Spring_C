#pragma once
#include "../ActorBase.h"
#include "../../Common/AnimationController.h"

class WeponMark;
class Wepon;
class EffectController;

class CharactorBase :
    public ActorBase
{
public:
    //回転保管量
    static constexpr float ROTATE_KEEP = 0.2f;

    //落下中判定の最低速度
    static constexpr float FALLING_SPEED_NIN = 0.9f;

    //押し出し距離
    static constexpr float PUSH_OUT_DIS = 2.0f;



    // 衝突判定種別
    enum class COLLIDER_TYPE
    {
        LINE,
        CAPSULE,
        MODEL,
        VIEW_RANGE,
        SPHERE,
        MAX,
    };

  

    // コンストラクタ
    CharactorBase(void);
    // デストラクタ
    virtual ~CharactorBase(void) override;

    // 更新
    virtual void Update(void) override;
    // 描画
    virtual void Draw(void) override;
    // 解放
    virtual void Release(void) override;

    //hp
    virtual int GetHp(void) const { return 0; }
    
    virtual int GetHpMax(void) const { return HP_MAX; }

    const Wepon* GetUseWepon(void) const { return wepon_; }

    virtual int GetAttack(void) const { return attack_; }

    void RemoveHitColliderByShapeAndTag(ColliderBase::SHAPE shape, ColliderBase::TAG tag);

protected:

    enum class LEVEL_LENGTH
    {
       LEVEL_1,
       LEVEL_2,
       LEVEL_3,
       LEVEL_4,
       LEVEL_5,
    };

    enum class LEVEL_RADIUS
    {
        LEVEL_1,
        LEVEL_2,
        LEVEL_3,
        LEVEL_4,
        LEVEL_5,
    };

    enum class LEVEL_SPEED
    {
        LEVEL_1,
        LEVEL_2,
        LEVEL_3,
        LEVEL_4,
        LEVEL_5,
    };

    enum class LEVEL_ATTACK
    {
		LEVEL_1,
		LEVEL_2,
		LEVEL_3,
		LEVEL_4,
		LEVEL_5,
	};

    enum class POWER_UP
    {
        LENGTH = 0,
        RADIUS,
        SPEED,
        ATTACK,
        MAX,
    };

    // 最大落下速度
    static constexpr float MAX_FALL_SPEED = -30.0f;

    // 衝突時の押し戻し試行回数
    static constexpr int CNT_TRY_COLLISION = 20;
    // 衝突時の押し戻し量
    static constexpr float COLLISION_BACK_DIS = 1.0f;

    //長さレベル（LEVEL_1
    static constexpr float LEVEL_1_LENGTH = 500.0f;
    //長さレベル（LEVEL_2
    static constexpr float LEVEL_2_LENGTH = 750.0f;
    //長さレベル（LEVEL_3
    static constexpr float LEVEL_3_LENGTH = 1000.0f;
    //長さレベル（LEVEL_4
    static constexpr float LEVEL_4_LENGTH = 1250.0f;
    //長さレベル（LEVEL_5
    static constexpr float LEVEL_5_LENGTH = 1500.0f;

    //半径レベル(LEVEL_1
    static constexpr float LEVEL_1_RADIUS = 20.0f;
    //半径レベル（LEVEL_2
    static constexpr float LEVEL_2_RADIUS = 60.0f;
    //半径レベル（LEVEL_3
    static constexpr float LEVEL_3_RADIUS = 100.0f;
    //半径レベル（LEVEL_4
    static constexpr float LEVEL_4_RADIUS = 140.0f;
    //半径レベル（LEVEL_5
    static constexpr float LEVEL_5_RADIUS = 180.0f;


    //移動速度（LEVEL_1
    static constexpr float LEVEL_1_MOVE_SPEED = 30.0f;
    //移動速度（LEVEL_2
    static constexpr float LEVEL_2_MOVE_SPEED = 40.0f;
    //移動速度（LEVEL_3
    static constexpr float LEVEL_3_MOVE_SPEED = 50.0f;
    //移動速度（LEVEL_4
    static constexpr float LEVEL_4_MOVE_SPEED = 60.0f;
    //移動速度（LEVEL_5
    static constexpr float LEVEL_5_MOVE_SPEED = 70.0f;

    //移動速度（LEVEL_1
    static constexpr float LEVEL_1_ATTACK_SPEED = 50.0f;
    //移動速度（LEVEL_2
    static constexpr float LEVEL_2_ATTACK_SPEED = 60.0f;
    //移動速度（LEVEL_3
    static constexpr float LEVEL_3_ATTACK_SPEED = 70.0f;
    //移動速度（LEVEL_4
    static constexpr float LEVEL_4_ATTACK_SPEED = 80.0f;
    //移動速度（LEVEL_5
    static constexpr float LEVEL_5_ATTACK_SPEED = 90.0f;

    //攻撃力（LEVEL_1
    static constexpr int LEVEL_1_ATTACK = 1;
    //攻撃力（LEVEL_2
    static constexpr int LEVEL_2_ATTACK = 2;
    //攻撃力（LEVEL_3
    static constexpr int LEVEL_3_ATTACK = 3;

    //level表記
    static constexpr VECTOR SP_RA_TEXT_POS = { 510,75,310 };
    static constexpr VECTOR LE_AT_TEXT_POS = { 710,75,110 };
    //level表記
    static constexpr VECTOR SP_RA_ROG_POS = { 550,100,350 };
    static constexpr VECTOR LE_AT_ROG_POS = { 750,100,150 };
    

    //プレイヤーのサイズ
    static constexpr VECTOR PLAYER_SIZE = { 0.5f, 0.5f, 0.5f };
    //アイテムサイズ
    static constexpr VECTOR ITEM_SIZE = { 1.0f, 1.0f, 1.0f };

    // 衝突判定用カプセル球体半径
    static constexpr float COL_CAPSULE_RADIUS = 60.0f;


    static constexpr int HP_MAX = 50;

    static constexpr float RESPAWN_POS_Y = -10.0f;

    // 移動速度(通常)
    static constexpr float SPEED_MOVE = 15.0f;


    // 衝突判定用線分開始
    static constexpr VECTOR COL_LINE_START_LOCAL_POS = { 0.0f, 80.0f, 0.0f };
    // 衝突判定用線分終了
    static constexpr VECTOR COL_LINE_END_LOCAL_POS = { 0.0f, -120.0f, 0.0f };

    //初期値
    //回転
    static constexpr float INIT_ROT = 180.0f;
    //移動速度
    static constexpr float INIT_MOVE_SPEED = 0.25f;
    //減速量
    static constexpr float DECELERATION = 0.01f;


    //シェイク時間
    static constexpr int SHAKE_TIME = 10;

    //マークを設置量の最大値
    static constexpr int MARK_MAX = 2;

    //テキストサイズ
    //MAX
    static constexpr int TEXT_SIZE_MAX = 64;
    //MIN
    static constexpr int TEXT_SIZE_MIN = 16;


    std::vector<WeponMark*> weponMark_;
    Wepon* wepon_;

    EffectController* effect_;
    //アニメーションコントローラ
    AnimationController* anim_;
    // 移動方向
    VECTOR moveDir_;
    // 移動量
    VECTOR movePow_;
    // 移動前の座標
    VECTOR prevPos_;
    // ジャンプ量
    VECTOR jumpPow_;

    //長さレベル
    int langthImg_;
    LEVEL_LENGTH lengthLevel_;
    float length_;

    //半径レベル
    int radiusImg_;
    LEVEL_RADIUS radiusLevel_;
    float radius_;

    //スピードレベル
    int speedImg_;
    LEVEL_SPEED speedLevel_;
    float speed_;
    float attackSpeed_;

    //攻撃力レベル
    int attackImg_;
    LEVEL_ATTACK attackLevel_;
    int attack_;

    //パワーアップパラメータ設定
    POWER_UP powerUp_;

    //HP
    int hp_;
    // 移動スピード
    float moveSpeed_;
    // ジャンプの入力受付時間
    float stepJump_;
    // ジャンプ判定
    bool isJump_;
    // 丸影画像
    int imgShadow_;

    //SE
    int hitSeHandle_;
    int weponSeHandle_;

    // リソースロード
    virtual void InitLoad(void) override;
    // 更新系
    virtual void UpdateProcess(void) = 0;
    virtual void UpdateProcessPost(void) = 0;

    

    // 移動方向に応じた遅延回転
    void DelayRotate(void);
    // 重力計算
    void CalcGravityPow(void);
    // 衝突判定
    virtual void CollisionReserve(void) {}
    void Collision(void);
    void CollisionGravity(void);
    void CollisionCapsule(void);
    //リスポーン
    virtual void Respawn(void) = 0;
    
    //長さレベルの設定
    virtual void LengthLevelSet(LEVEL_LENGTH length) = 0;
    //半径レベルの設定
    virtual void RadiusLevelSet(LEVEL_RADIUS radius) = 0;
    //スピードレベルの設定
    virtual void SpeedLevelSet(LEVEL_SPEED speed) = 0;
    //攻撃力レベルの設定
    virtual void AttackLevelSet(LEVEL_ATTACK attack) = 0;
  

    //リアルシャドウ
    void DrawShadowMap(void);


    
};