#pragma once

/*
	Sprite & Background, Foreground Image Process
*/
#include "PixelEngine.h"

class Cartridge;
class PictureProcessor
{
	union
	{
		struct
		{
			uint8_t Used : 5;
			uint8_t SpriteOverflow : 1;
			uint8_t SpriteZerohit : 1;
			uint8_t VerticalBlank : 1;
		};

		uint8_t Register;
	} Status;  // Status Register  PPUSTATUS  $2002

	union
	{
		struct
		{
			uint8_t GrayScale : 1;
			uint8_t RenderBackgroundLeft : 1;
			uint8_t RenderSpriteLeft : 1;
			uint8_t RenderBackground : 1;
			uint8_t RenderSprite : 1;
			uint8_t EnhanceRed : 1;
			uint8_t EnhanceGreen : 1;
			uint8_t EnhanceBlue : 1;
		};

		uint8_t Register;
	} Mask;  // Mask Register  PPUMASK $2001

	union   
	{
		struct
		{
			uint8_t NameTableX : 1;
			uint8_t NameTableY : 1;
			uint8_t IncrementMode : 1;
			uint8_t PatternSprite : 1;
			uint8_t PatternBackground : 1;
			uint8_t SpriteSize : 1;
			uint8_t SlaveMode : 1;
			uint8_t EnableNMI : 1;
		};

		uint8_t Register;
	} Control; // Control Register  PPUCTRL  $2000

	union LoopRegister
	{
		struct
		{
			uint16_t CoarseX : 5;
			uint16_t CoarseY : 5;
			uint16_t NameTableX : 1;
			uint16_t NameTableY : 1;
			uint16_t FineY : 3;
			uint16_t Unused : 1;
		};

		uint16_t Register;
	};

	struct ObjctAttributeEntry
	{
		uint8_t Ypos;
		uint8_t TileID;
		uint8_t Attribute;
		uint8_t Xpos;
	} OAM[64];


	std::shared_ptr<Cartridge> cartridge;

	// PPU 구성요소
	uint8_t			Name[2][1024];  // 네임 테이블
	uint8_t			Palette[32];  // 색
	uint8_t			Pattern[2][4096];  // 패턴

	// DEBUG
	PixelEngine::Pixel  PixelScreen[0x40];
	PixelEngine::Sprite SpriteScreen = PixelEngine::Sprite(256, 240);
	PixelEngine::Sprite NameTable[2] = { PixelEngine::Sprite(256,240), PixelEngine::Sprite(256,240) };
	PixelEngine::Sprite PatternTable[2] = { PixelEngine::Sprite(128, 128), PixelEngine::Sprite(128,128) };

	// 픽셀 점 위치 정보
	int16_t ScanLine = 0;  // 스크린 보다 더 넓은 영역
	int16_t Cycle = 0;

	// 스크린영역부분만, CPU와 커뮤니케이션

	// 내부 CPU <-> PPU 통신용 -> 래치는 일정시간동안 데이터 기억
	uint8_t AddressLatch = 0;
	uint8_t PpuDataBuffer = 0;

	uint16_t PpuAddress = 0;

	LoopRegister VramAddress;
	LoopRegister TramAddress;


	// 수평 픽셀 오프셋 
	uint8_t FineX = 0;

	// Background Render
	uint8_t BgNextTileId = 0;
	uint8_t BgNextTileAttribute = 0;
	uint8_t BgNextTileLSB = 0;
	uint8_t BgNextTileMSB = 0;
	uint16_t BgShifterPatternLow = 0;
	uint16_t BgShifterPatternHigh = 0;
	uint16_t BgShifterAttributeLow = 0;
	uint16_t BgShifterAttributeHigh = 0;

	// OAM And Fore Sprite 
	uint8_t* POM = reinterpret_cast<uint8_t*>(OAM);
	uint8_t  OAMAddress = 0;

	ObjctAttributeEntry SpriteScanLine[8];
	uint8_t SpriteCount;   // Scan Line으로 부터 찾은 스프라이트
	uint8_t SpriteShifterPatternLow[8];
	uint8_t SpriteShifterPatternHigh[8];

	bool SpriteZeroHitPossible = false;
	bool SpriteZeroBeingRendered = false;
 
public:
	bool FrameComplete = false;

	bool NMI = false;
public:
	PictureProcessor();

	void Reset();

	// Cpu 버스 통한 커뮤니 케이션
	void CpuWrite(uint16_t AddressPosition, uint8_t Data);
	uint8_t CpuRead(uint16_t AddressPosition, bool ReadOnly = false);

	// PPU Bus 통해 커뮤니케이션
	void PpuWrite(uint16_t AddressPosition, uint8_t Data);
	uint8_t PpuRead(uint16_t AddressPosition, bool ReadOnly = false);


	// Interface 
	void ConnectCartridge(const std::shared_ptr<Cartridge>& cartridge);
	void Clock();


	// Object Attribute Memory
	uint8_t* GetOAMPointer();

	PixelEngine::Pixel& GetColorFromPalette(uint8_t Palette, uint8_t Pixel);
	PixelEngine::Sprite& GetScreen();
	PixelEngine::Sprite& GetNameTable(uint8_t i);
	PixelEngine::Sprite& GetPatternTable(uint8_t i, uint8_t Palette);
};

