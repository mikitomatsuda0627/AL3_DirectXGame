#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() { delete sprite_; 
delete model_;
	/*delete model_;*/
}
void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	textureHandle_ = TextureManager::Load("mario.jpg");
	sprite_ = Sprite::Create(textureHandle_, {100, 50});
	model_ = Model::Create();
	worldTransform_.Initialize();
	viewProjection_.Initialize();
	textureHandle_ = TextureManager::Load("mario.jpg");
	model_ = Model::Create();
	
	// x,y,zのスケーリング設定
	worldTransform_.scale_ = {5.0f, 5.0f, 5.0f};
	//x,y,z軸回りの回転角を設定
	worldTransform_.rotation_ = {XM_PI / 4.0f, XM_PI / 4.0f, 0.0f};
	// x,y,z軸回りの平行移動を設定
	worldTransform_.translation_ = {10.0f, 10.0f, 10.0f};
	//	soundDateHandle_ = audio_->LoadWave("fanfare.wav");
	//	audio_->PlayWave(soundDateHandle_);
	//	voiceHandle_ = audio_ -> PlayWave(soundDateHandle_, true);
	//}
	worldTransform_.Initialize();
	viewProjection_.Initialize();
}

void GameScene::Update() { 
	//translataton
	std::string strDebug = std::string("transLation:(") +
	                       std::to_string(worldTransform_.translation_.x) + std::string("") +
	                       std::to_string(worldTransform_.translation_.y) + std::string("") +
	                       std::to_string(worldTransform_.translation_.z) + std::string(",)");
	debugText_->Print(strDebug, 50, 50, 1.0f);
	//rotation
	std::string strDebug2 = std::string("roration:(") + 
	                        std::to_string(worldTransform_.rotation_.x) + std::string("") +
	                        
	                        std::to_string(worldTransform_.rotation_.y) + std::string("") +
	                        std::to_string(worldTransform_.rotation_.z) + std::string(",)");
	debugText_->Print(strDebug2, 50, 70, 1.0f);
	//scale
	std::string strDebug3 = std::string("scale:(") +
	                        std::to_string(worldTransform_.scale_.x) + std::string("") +

	                        std::to_string(worldTransform_.scale_.y) + std::string("") +
	                        std::to_string(worldTransform_.scale_.z) + std::string(",)");
	debugText_->Print(strDebug3, 50, 90, 1.0f);
	//	XMFLOAT2 position = sprite_->GetPosition();
//	position.x += 2.0f;
//	position.y += 1.0f;
//	sprite_->SetPosition(position);
//	/*debugText_->Print("kaizokuou ni oreha naru.", 50, 50, 1.0f);*/
//	debugText_->SetPos(50, 70);
//	/*debugText_->Printf("year:%d", 2001);*/
//	value_++;
//	std::string strDebag = std::string("Value:") + std::to_string(value_);
//	debugText_->Print(strDebag, 50, 50, 1.0f);


//	if (input_->TriggerKey(DIK_SPACE)) {
//		audio_->StopWave(voiceHandle_);
//	}
}

void GameScene::Draw() {
	
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);
	//textureHandle_ = TextureManager::Load("mario.jpg");
	
	/// <summary>
	
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	//sprite_->Draw();
	// デバッグテキストの描画
	debugText_->DrawAll(commandList);

	//
	// スプライト描画後処理
	Sprite::PostDraw();


#pragma endregion
}
