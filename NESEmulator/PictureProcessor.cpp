#include "Precompile.h"
#include "PictureProcessor.h"
#include "Cartridge.h"

PictureProcessor::PictureProcessor()
{
	Reset();
	PixelScreen[0x00] = PixelEngine::Pixel(84, 84, 84);
	PixelScreen[0x01] = PixelEngine::Pixel(0, 30, 116);
	PixelScreen[0x02] = PixelEngine::Pixel(8, 16, 144);
	PixelScreen[0x03] = PixelEngine::Pixel(48, 0, 136);
	PixelScreen[0x04] = PixelEngine::Pixel(68, 0, 100);
	PixelScreen[0x05] = PixelEngine::Pixel(92, 0, 48);
	PixelScreen[0x06] = PixelEngine::Pixel(84, 4, 0);
	PixelScreen[0x07] = PixelEngine::Pixel(60, 24, 0);
	PixelScreen[0x08] = PixelEngine::Pixel(32, 42, 0);
	PixelScreen[0x09] = PixelEngine::Pixel(8, 58, 0);
	PixelScreen[0x0A] = PixelEngine::Pixel(0, 64, 0);
	PixelScreen[0x0B] = PixelEngine::Pixel(0, 60, 0);
	PixelScreen[0x0C] = PixelEngine::Pixel(0, 50, 60);
	PixelScreen[0x0D] = PixelEngine::Pixel(0, 0, 0);
	PixelScreen[0x0E] = PixelEngine::Pixel(0, 0, 0);
	PixelScreen[0x0F] = PixelEngine::Pixel(0, 0, 0);

	PixelScreen[0x10] = PixelEngine::Pixel(152, 150, 152);
	PixelScreen[0x11] = PixelEngine::Pixel(8, 76, 196);
	PixelScreen[0x12] = PixelEngine::Pixel(48, 50, 236);
	PixelScreen[0x13] = PixelEngine::Pixel(92, 30, 228);
	PixelScreen[0x14] = PixelEngine::Pixel(136, 20, 176);
	PixelScreen[0x15] = PixelEngine::Pixel(160, 20, 100);
	PixelScreen[0x16] = PixelEngine::Pixel(152, 34, 32);
	PixelScreen[0x17] = PixelEngine::Pixel(120, 60, 0);
	PixelScreen[0x18] = PixelEngine::Pixel(84, 90, 0);
	PixelScreen[0x19] = PixelEngine::Pixel(40, 114, 0);
	PixelScreen[0x1A] = PixelEngine::Pixel(8, 124, 0);
	PixelScreen[0x1B] = PixelEngine::Pixel(0, 118, 40);
	PixelScreen[0x1C] = PixelEngine::Pixel(0, 102, 120);
	PixelScreen[0x1D] = PixelEngine::Pixel(0, 0, 0);
	PixelScreen[0x1E] = PixelEngine::Pixel(0, 0, 0);
	PixelScreen[0x1F] = PixelEngine::Pixel(0, 0, 0);

	PixelScreen[0x20] = PixelEngine::Pixel(236, 238, 236);
	PixelScreen[0x21] = PixelEngine::Pixel(76, 154, 236);
	PixelScreen[0x22] = PixelEngine::Pixel(120, 124, 236);
	PixelScreen[0x23] = PixelEngine::Pixel(176, 98, 236);
	PixelScreen[0x24] = PixelEngine::Pixel(228, 84, 236);
	PixelScreen[0x25] = PixelEngine::Pixel(236, 88, 180);
	PixelScreen[0x26] = PixelEngine::Pixel(236, 106, 100);
	PixelScreen[0x27] = PixelEngine::Pixel(212, 136, 32);
	PixelScreen[0x28] = PixelEngine::Pixel(160, 170, 0);
	PixelScreen[0x29] = PixelEngine::Pixel(116, 196, 0);
	PixelScreen[0x2A] = PixelEngine::Pixel(76, 208, 32);
	PixelScreen[0x2B] = PixelEngine::Pixel(56, 204, 108);
	PixelScreen[0x2C] = PixelEngine::Pixel(56, 180, 204);
	PixelScreen[0x2D] = PixelEngine::Pixel(60, 60, 60);
	PixelScreen[0x2E] = PixelEngine::Pixel(0, 0, 0);
	PixelScreen[0x2F] = PixelEngine::Pixel(0, 0, 0);

	PixelScreen[0x30] = PixelEngine::Pixel(236, 238, 236);
	PixelScreen[0x31] = PixelEngine::Pixel(168, 204, 236);
	PixelScreen[0x32] = PixelEngine::Pixel(188, 188, 236);
	PixelScreen[0x33] = PixelEngine::Pixel(212, 178, 236);
	PixelScreen[0x34] = PixelEngine::Pixel(236, 174, 236);
	PixelScreen[0x35] = PixelEngine::Pixel(236, 174, 212);
	PixelScreen[0x36] = PixelEngine::Pixel(236, 180, 176);
	PixelScreen[0x37] = PixelEngine::Pixel(228, 196, 144);
	PixelScreen[0x38] = PixelEngine::Pixel(204, 210, 120);
	PixelScreen[0x39] = PixelEngine::Pixel(180, 222, 120);
	PixelScreen[0x3A] = PixelEngine::Pixel(168, 226, 144);
	PixelScreen[0x3B] = PixelEngine::Pixel(152, 226, 180);
	PixelScreen[0x3C] = PixelEngine::Pixel(160, 214, 228);
	PixelScreen[0x3D] = PixelEngine::Pixel(160, 162, 160);
	PixelScreen[0x3E] = PixelEngine::Pixel(0, 0, 0);
	PixelScreen[0x3F] = PixelEngine::Pixel(0, 0, 0);
}

void PictureProcessor::Reset()
{
	FineX = 0;
	AddressLatch = 0;
	PpuAddress = 0;
	PpuDataBuffer = 0;
	ScanLine = 0;
	Cycle = 0;
	VramAddress.Register = 0;
	TramAddress.Register = 0;
	Control.Register = 0;
	Mask.Register = 0;
	Status.Register = 0;

	BgNextTileId = 0;
	BgNextTileAttribute = 0;
	BgNextTileLSB = 0;
	BgNextTileMSB = 0;
	BgShifterPatternLow = 0;
	BgShifterPatternHigh = 0;
	BgShifterAttributeLow = 0;
	BgShifterAttributeHigh = 0;
}

void PictureProcessor::CpuWrite(uint16_t AddressPosition, uint8_t Data)
{
	switch (AddressPosition)
	{
	case 0x0000: // Control
		Control.Register = Data;
		TramAddress.NameTableX = Control.NameTableX;
		TramAddress.NameTableY = Control.NameTableY;
		break;
	case 0x0001: // Mask
		Mask.Register = Data;
		break;
	case 0x0002: // Status
		break;
	case 0x0003: // OAM Address
		OAMAddress = Data;
		break;
	case 0x0004: // OAM Data
		POM[OAMAddress] = Data;
		break;
	case 0x0005: // Scroll
		if (AddressLatch == 0)
		{
			FineX = Data & 0x07;
			TramAddress.CoarseX = Data >> 3;
			AddressLatch  = 1;
		}
		else
		{
			TramAddress.FineY = Data & 0x07;
			TramAddress.CoarseY = Data >> 3;
			AddressLatch = 0;
		}
		break;
	case 0x0006: // PPU Address
		if (AddressLatch == 0)
		{
			TramAddress.Register = static_cast<uint16_t>
				(((Data & 0x3F) << 8) | (TramAddress.Register & 0x00FF));
			AddressLatch = 1;
		}
		else
		{
			TramAddress.Register = (TramAddress.Register & 0xFF00) | Data;
			VramAddress = TramAddress;
			AddressLatch = 0;
		}
		break;
	case 0x0007: // PPU Data
		PpuWrite(VramAddress.Register, Data);
		VramAddress.Register += (Control.IncrementMode ? 32 : 1);
		break;
	}
}

uint8_t PictureProcessor::CpuRead(uint16_t AddressPosition, bool ReadOnly)
{
	uint8_t data = 0;

	if (ReadOnly)
	{
		switch (AddressPosition)
		{
		case 0x0000: // Control
			data = Control.Register;
			break;
		case 0x0001: // Mask
			data = Mask.Register;
			break;
		case 0x0002: // Status
			data = Status.Register;
			break;
		case 0x0003: // OAM Address
			break;
		case 0x0004: // OAM Data
			break;
		case 0x0005: // Scroll
			break;
		case 0x0006: // PPU Address
			break;
		case 0x0007: // PPU Data
			break;
		}
	}
	else
	{
		switch (AddressPosition)
		{
		case 0x0000: // Control
			break;
		case 0x0001: // Mask
			break;
		case 0x0002: // Status
			// 상태 레지스터로부터 데이터를 읽어온다.
			data = (Status.Register & 0xE0) | (PpuDataBuffer & 0x1F);

			Status.VerticalBlank = 0;
			AddressLatch = 0;
			break;
		case 0x0003: // OAM Address
			break;
		case 0x0004: // OAM Data
			data = POM[OAMAddress];
			break;
		case 0x0005: // Scroll
			break;
		case 0x0006: // PPU Address
			break;
		case 0x0007: // PPU Data
			data = PpuDataBuffer;
			PpuDataBuffer = PpuRead(VramAddress.Register);

			if (VramAddress.Register >= 0x3F00)
				data = PpuDataBuffer;

			VramAddress.Register += (Control.IncrementMode ? 32 : 1);
			break;
		}
	}

	return data;
}

void PictureProcessor::PpuWrite(uint16_t AddressPosition, uint8_t Data)
{
	AddressPosition &= 0x3FFF;

	if (cartridge->PpuWrite(AddressPosition, Data))
	{

	}
	else if (AddressPosition >= 0x0000 && AddressPosition <= 0x1FFF) // 패턴 메모리 주소
	{
		Pattern[(AddressPosition & 0x1000) >> 12][AddressPosition & 0x0FFF] = Data;
	}
	else if (AddressPosition >= 0x2000 && AddressPosition <= 0x3EFF)  // NameTable & 일부 Pattles 주소 
	{
		AddressPosition &= 0x0FFF;

		if (cartridge->mirror == Cartridge::MIRROR::VERTICAL)
		{
			if (AddressPosition >= 0x0000 && AddressPosition <= 0x03FF)
				Name[0][AddressPosition & 0x03FF] = Data;
			if (AddressPosition >= 0x0400 && AddressPosition <= 0x07FF)
				 Name[1][AddressPosition & 0x03FF] = Data;
			if (AddressPosition >= 0x0800 && AddressPosition <= 0x0BFF)
				Name[0][AddressPosition & 0x03FF] = Data;
			if (AddressPosition >= 0x0C00 && AddressPosition <= 0x0FFF)
				Name[1][AddressPosition & 0x03FF] = Data;
		}
		else if (cartridge->mirror == Cartridge::MIRROR::HORIZONTAL)
		{

			// Horizontal
			if (AddressPosition >= 0x0000 && AddressPosition <= 0x03FF)
				Name[0][AddressPosition & 0x03FF] = Data;
			if (AddressPosition >= 0x0400 && AddressPosition <= 0x07FF)
				Name[0][AddressPosition & 0x03FF] = Data;
			if (AddressPosition >= 0x0800 && AddressPosition <= 0x0BFF)
				Name[1][AddressPosition & 0x03FF] = Data;
			if (AddressPosition >= 0x0C00 && AddressPosition <= 0x0FFF)
				 Name[1][AddressPosition & 0x03FF] = Data;
		}
	}
	else if (AddressPosition >= 0x3F00 && AddressPosition <= 0x3FFF)  // Pattles 주소
	{
		AddressPosition &= 0x001F;

		switch (AddressPosition)
		{
		case 0x0010:
			AddressPosition = 0x0000;
			break;
		case 0x0014:
			AddressPosition = 0x0004;
			break;
		case 0x0018:
			AddressPosition = 0x0008;
			break;
		case 0x001C:
			AddressPosition = 0x000C;
			break;
		}

		Palette[AddressPosition] = Data;
	}
}

uint8_t PictureProcessor::PpuRead(uint16_t AddressPosition, bool ReadOnly)
{
	uint8_t data = 0x00;

	AddressPosition &= 0x3FFF;

	if (cartridge->PpuRead(AddressPosition, data))
	{

	}
	else if (AddressPosition >= 0x0000 && AddressPosition <= 0x1FFF)
	{
		data = Pattern[(AddressPosition & 0x1000) >> 12][AddressPosition & 0x0FFF];
	}
	else if (AddressPosition >= 0x2000 && AddressPosition <= 0x3EFF)
	{
		AddressPosition &= 0x0FFF;

		if (cartridge->mirror == Cartridge::MIRROR::VERTICAL)
		{
			if (AddressPosition >= 0x0000 && AddressPosition <= 0x03FF)
				data = Name[0][AddressPosition & 0x03FF];
			if (AddressPosition >= 0x0400 && AddressPosition <= 0x07FF)
				data = Name[1][AddressPosition & 0x03FF];
			if (AddressPosition >= 0x0800 && AddressPosition <= 0x0BFF)
				data = Name[0][AddressPosition & 0x03FF];
			if (AddressPosition >= 0x0C00 && AddressPosition <= 0x0FFF)
				data = Name[1][AddressPosition & 0x03FF];
		}
		else if (cartridge->mirror == Cartridge::MIRROR::HORIZONTAL)
		{

			// Horizontal
			if (AddressPosition >= 0x0000 && AddressPosition <= 0x03FF)
				data = Name[0][AddressPosition & 0x03FF];
			if (AddressPosition >= 0x0400 && AddressPosition <= 0x07FF)
				data = Name[0][AddressPosition & 0x03FF];
			if (AddressPosition >= 0x0800 && AddressPosition <= 0x0BFF)
				data = Name[1][AddressPosition & 0x03FF];
			if (AddressPosition >= 0x0C00 && AddressPosition <= 0x0FFF)
				data = Name[1][AddressPosition & 0x03FF];
		}
	}
	else if (AddressPosition >= 0x3F00 && AddressPosition <= 0x3FFF)
	{
		AddressPosition &= 0x001F;

		switch (AddressPosition)
		{
		case 0x0010:
			AddressPosition = 0x0000;
			break;
		case 0x0014:
			AddressPosition = 0x0004;
			break;
		case 0x0018:
			AddressPosition = 0x0008;
			break;
		case 0x001C:
			AddressPosition = 0x000C;
			break;
		}

		data = Palette[AddressPosition] & (Mask.GrayScale ? 0x30 : 0x3F);
	}


	return data;
}

void PictureProcessor::ConnectCartridge(const std::shared_ptr<Cartridge>& cartridge)
{
	this->cartridge = cartridge;
}

void PictureProcessor::Clock()
{
	// 픽셀 수평 스크롤링
	auto IncrementScrollX = [&]() 
	{
		if (Mask.RenderBackground || Mask.RenderSprite)
		{
			if (VramAddress.CoarseX == 31)
			{
				VramAddress.CoarseX = 0;
				VramAddress.NameTableX = ~VramAddress.NameTableX;
			}
			else
			{
				VramAddress.CoarseX++;
			}
		}
	};

	auto IncrementScrollY = [&]()
	{
		if (Mask.RenderBackground || Mask.RenderSprite)
		{
			if (VramAddress.FineY < 7)
			{
				VramAddress.FineY++;
			}
			else
			{
				VramAddress.FineY = 0;

				// 수직 네임테이블 타겟 스왑
				if (VramAddress.CoarseY == 29)
				{
					VramAddress.CoarseY = 0;
					VramAddress.NameTableY = ~VramAddress.NameTableY;
				}
				else if (VramAddress.CoarseY == 31)
				{
					// 포인터 현재 위치 Attrib메모리에 있으므로 초기화
					VramAddress.CoarseY = 0;
				}
				else
				{
					VramAddress.CoarseY++;
				}
			}
		}
	};

	auto TransferAddressX = [&]()
	{
		if (Mask.RenderBackground || Mask.RenderSprite)
		{
			VramAddress.NameTableX = TramAddress.NameTableX;
			VramAddress.CoarseX = TramAddress.CoarseX;
		}
	};

	auto TransferAddressY = [&]()
	{
		if (Mask.RenderBackground || Mask.RenderSprite)
		{
			VramAddress.FineY = TramAddress.FineY;
			VramAddress.NameTableY = TramAddress.NameTableY;
			VramAddress.CoarseY = TramAddress.CoarseY;
		}
	};

	auto UpdateShifter = [&]()
	{
		if (Mask.RenderBackground)
		{
			BgShifterPatternHigh <<= 1;
			BgShifterPatternLow <<= 1;

			BgShifterAttributeHigh <<= 1;
			BgShifterAttributeLow <<= 1;
		}

		if (Mask.RenderSprite && Cycle >= 1 && Cycle < 258)
		{
			for (int i = 0; i < SpriteCount; ++i)
			{
				if (SpriteScanLine[i].Xpos > 0)
				{
					SpriteScanLine[i].Xpos--;
				}
				else
				{
					SpriteShifterPatternLow[i] <<= 1;
					SpriteShifterPatternHigh[i] <<= 1;
				}
			}
		}
	};

	auto LoadBackgroundShifters = [&]()
	{
		BgShifterPatternLow = (BgShifterPatternLow & 0xFF00) | BgNextTileLSB;
		BgShifterPatternHigh = (BgShifterPatternHigh & 0xFF00) | BgNextTileMSB;


		BgShifterAttributeLow = (BgShifterAttributeLow & 0xFF00) | ((BgNextTileAttribute & 0b01) ? 0xFF : 0x00);
		BgShifterAttributeHigh = (BgShifterAttributeHigh & 0xFF00) | ((BgNextTileAttribute & 0b10) ? 0xFF : 0x00);

	};

	if (ScanLine >= -1 && ScanLine < 240) // Visible Range
	{
		if (ScanLine == 0 && Cycle == 0)
		{
			Cycle = 1;
		}

		if (ScanLine == -1 && Cycle == 1)  // Screen 윗 부분
		{
			Status.VerticalBlank = 0;
			Status.SpriteOverflow = 0;
			Status.SpriteZerohit = 0;

			for (int i = 0; i < 8; ++i)
			{
				SpriteShifterPatternHigh[i] = 0;
				SpriteShifterPatternLow[i] = 0;
			}
		}

		if ((Cycle >= 2 && Cycle < 258) || (Cycle >= 321 && Cycle < 338))
		{
			UpdateShifter();

			switch ((Cycle - 1) % 8)
			{
			case 0:
				LoadBackgroundShifters();

				BgNextTileId = PpuRead(0x2000 | (VramAddress.Register & 0x0FFF));

				//   0                1
				// 0 +----------------+----------------+
				//   |                |                |
				//   |                |                |
				//   |    (32x32)     |    (32x32)     |
				//   |                |                |
				//   |                |                |
				// 1 +----------------+----------------+
				//   |                |                |
				//   |                |                |
				//   |    (32x32)     |    (32x32)     |
				//   |                |                |
				//   |                |                |
				//   +----------------+----------------+
				break;
			case 2:
				// +----+----+			    +----+----+
				// | TL | TR |			    | ID | ID |
				// +----+----+ where TL =   +----+----+
				// | BL | BR |			    | ID | ID |
				// +----+----+			    +----+----+

				BgNextTileAttribute = PpuRead(0x23C0 | 
					(VramAddress.NameTableY << 11)
					| (VramAddress.NameTableX << 10)
					| ((VramAddress.CoarseY >> 2) << 3)
					| (VramAddress.CoarseX >> 2)
				);

				if (VramAddress.CoarseY & 0x02)
					BgNextTileAttribute >>= 4;
				if (VramAddress.CoarseX & 0x02)
					BgNextTileAttribute >>= 2;
				BgNextTileAttribute &= 0x03;
											
				break;
			case 4:
				BgNextTileLSB = PpuRead((Control.PatternBackground << 12)
					+ ((uint16_t)BgNextTileId << 4)
					+ (VramAddress.FineY) + 0);
				break;
			case 6:
				BgNextTileMSB = PpuRead((Control.PatternBackground << 12)
					+ ((uint16_t)BgNextTileId << 4)
					+ (VramAddress.FineY) + 8);
				break;
			case 7:
				IncrementScrollX();
				break;
			}
	
		}

		if (Cycle == 256)
			IncrementScrollY();

		if (Cycle == 257)
		{
			LoadBackgroundShifters();
			TransferAddressX();
		}

		if (Cycle == 338 || Cycle == 340)
		{
			BgNextTileId = PpuRead(0x2000 | (VramAddress.Register & 0x0FFF));
		}

		if (ScanLine == -1 && Cycle >= 280 && Cycle < 305)
		{
			TransferAddressY();
		}

		/// Foreground Render
		if (Cycle == 257 && ScanLine >= 0)
		{
			std::memset(SpriteScanLine, 0xFF, 8 * sizeof(ObjctAttributeEntry));
			SpriteCount = 0;

			// Search Visible Sprite
			uint8_t OAMEntry = 0;
			SpriteZeroHitPossible = false;

			for (uint8_t i = 0; i < 8; ++i)
			{
				SpriteShifterPatternHigh[i] = 0;
				SpriteShifterPatternLow[i] = 0;
			}

			while (OAMEntry < 64 && SpriteCount < 9)  // 첫번째로 보이는 8개 스프라이트 찾는다.
			{
				int16_t diff = ((int16_t)ScanLine - (int16_t)(OAM[OAMEntry].Ypos));

				if (diff >= 0 && diff < (Control.SpriteSize ? 16 : 8))  // Sprite height 
				{
					// Next Scanline에 보이게 한다.
					if (SpriteCount < 8)
					{
						if (OAMEntry == 0)
						{
							SpriteZeroHitPossible = true;
						}

						memcpy(&SpriteScanLine[SpriteCount], &OAM[OAMEntry], sizeof(ObjctAttributeEntry));
						++SpriteCount;
					}
				}

				OAMEntry++;
			}

			Status.SpriteOverflow = (SpriteCount > 8);
		}

		if (Cycle == 340)
		{
			for (uint8_t i = 0; i < SpriteCount; ++i)
			{
				uint8_t SpritePatternBitsLow, SpritePatternBitsHigh;
				uint16_t SpritePatternAddressLow, SpritePatternAddressHigh;

				if (!Control.SpriteSize)
				{
					// 8 X 8
					if (!(SpriteScanLine[i].Attribute & 0x80))
					{
						SpritePatternAddressLow = (Control.PatternSprite << 12) | (SpriteScanLine[i].TileID << 4)
							| (ScanLine - SpriteScanLine[i].Ypos);
					}
					else
					{
						// Filp Vertically
						SpritePatternAddressLow = (Control.PatternSprite << 12) | (SpriteScanLine[i].TileID << 4)
							| 7 - (ScanLine - SpriteScanLine[i].Ypos);
					}
				}
				else
				{
					 // 8 * 16
					if (!(SpriteScanLine[i].Attribute & 0x80))
					{
						if (ScanLine - SpriteScanLine[i].Ypos < 8)
						{
							// 상위 반쪽 타일 읽어오기
							SpritePatternAddressLow = (((SpriteScanLine[i].TileID & 0x01) << 12) 
								| ((SpriteScanLine[i].TileID & 0x01) << 4)
								| ((ScanLine - SpriteScanLine[i].Ypos) & 0x07));
						}
						else
						{
							// 하위 반쪽 타일 읽어오기
							SpritePatternAddressLow = (((SpriteScanLine[i].TileID & 0x01) << 12)
								| (((SpriteScanLine[i].TileID & 0x01) + 1) << 4)
								| ((ScanLine - SpriteScanLine[i].Ypos) & 0x07));
						}
					}
					else
					{
						// Filp Vertically
						if (ScanLine - SpriteScanLine[i].Ypos < 8)
						{
							SpritePatternAddressLow = ((SpriteScanLine[i].TileID & 0x01) << 12)
								| (((SpriteScanLine[i].TileID & 0xFE) + 1) << 4)
								| (7 - (ScanLine - SpriteScanLine[i].Ypos) & 0x07);
						}
						else
						{
							SpritePatternAddressLow = ((SpriteScanLine[i].TileID & 0x01) << 12)
								| (((SpriteScanLine[i].TileID & 0xFE)) << 4)
								| (7 - (ScanLine - SpriteScanLine[i].Ypos) & 0x07);
						}
					}
				}

				SpritePatternAddressHigh = SpritePatternAddressLow + 8;
				SpritePatternBitsLow = PpuRead(SpritePatternAddressLow);
				SpritePatternBitsHigh = PpuRead(SpritePatternAddressHigh);


				if (SpriteScanLine[i].Attribute & 0x40)
				{
					auto FlipByte = [](uint8_t byte)
					{
						byte = (byte & 0xF0) >> 4 | (byte & 0x0F) << 4;
						byte = (byte & 0xCC) >> 2 | (byte & 0x33) << 2;
						byte = (byte & 0xAA) >> 1 | (byte & 0x55) << 1;

						return byte;
					};

					// Filp Pattern Horizontally
					SpritePatternBitsLow = FlipByte(SpritePatternBitsLow);
					SpritePatternBitsHigh = FlipByte(SpritePatternBitsHigh);
				}

				SpriteShifterPatternLow[i] = SpritePatternBitsLow;
				SpriteShifterPatternHigh[i] = SpritePatternBitsHigh;
			}
		}
	}

	if (ScanLine == 240)
	{
		// Post Render Scanline - Do Nothing!
	}

	if (ScanLine >= 241 && ScanLine < 261)
	{
		if (ScanLine == 241 && Cycle == 1)
		{
			// Effectively end of frame, so set vertical blank flag
			Status.VerticalBlank = 1;


			if (Control.EnableNMI)
				NMI = true;
		}
	}

	uint8_t BackgroundPixel = 0;
	uint8_t BackgroundPalette = 0;

	if (Mask.RenderBackground)  // 매끄로운 스크롤을 위해, 모든 배경 렌더링을 설정된 픽셀 수로 오프셋 처리
	{
		uint16_t BitMux = 0x8000 >> FineX;

		uint8_t Pixel0 = (BgShifterPatternLow & BitMux) > 0;
		uint8_t Pixel1 = (BgShifterPatternHigh & BitMux) > 0;

		BackgroundPixel = (Pixel1 << 1) | Pixel0;

		uint8_t Palette0 = (BgShifterAttributeLow & BitMux) > 0;
		uint8_t Palette1 = (BgShifterAttributeHigh & BitMux) > 0;

		BackgroundPalette = (Palette1 << 1) | Palette0;
	}

	uint8_t ForegroundPixel = 0;
	uint8_t ForegroundPalette = 0;
	uint8_t ForegroundPriority = 0; // Z-Order

	if (Mask.RenderSprite)
	{
		SpriteZeroBeingRendered = false;

		for (uint8_t i = 0; i < SpriteCount; ++i)
		{
			if (SpriteScanLine[i].Xpos == 0)
			{
				uint8_t ForePixelLow = (SpriteShifterPatternLow[i] & 0x80) > 0;
				uint8_t ForePixelHigh = (SpriteShifterPatternHigh[i] & 0x80) > 0;

				ForegroundPixel = (ForePixelHigh << 1) | ForePixelLow;
				ForegroundPalette = (SpriteScanLine[i].Attribute & 0x03) + 0x04;
				ForegroundPriority = (SpriteScanLine[i].Attribute & 0x20) == 0;

				if (ForegroundPixel != 0)
				{
					if(i == 0)
						SpriteZeroBeingRendered = true;
					
					break;
				}
			}
		}
	}

	// Output Graphic
	uint8_t Pixel = 0;
	uint8_t Palette = 0;

	if (BackgroundPixel == 0 && ForegroundPixel == 0)
	{
		Pixel = 0;
		Palette = 0;
	}
	else if (BackgroundPixel == 0 && ForegroundPixel > 0)
	{
		Pixel = ForegroundPixel;
		Palette = ForegroundPalette;
	}
	else if (BackgroundPixel > 0 && ForegroundPixel == 0)
	{
		Pixel = BackgroundPixel;
		Palette = BackgroundPalette;
	}
	else if(BackgroundPixel > 0 && ForegroundPixel > 0)
	{
		if (ForegroundPriority)
		{
			Pixel = ForegroundPixel;
			Palette = ForegroundPalette;
		}
		else
		{
			Pixel = BackgroundPixel;
			Palette = BackgroundPalette;
		}

		if (SpriteZeroHitPossible && SpriteZeroBeingRendered)
		{
			if (Mask.RenderBackground & Mask.RenderSprite)
			{
				if (~(Mask.RenderBackgroundLeft | Mask.RenderSpriteLeft))
				{
					if (Cycle >= 9 && Cycle < 258)
					{
						Status.SpriteZerohit = 1;
					}
				}
				else
				{
					if (Cycle >= 1 && Cycle < 258)
					{
						Status.SpriteZerohit = 1;
					}
				}
			}
		}
	}


	SpriteScreen.SetPixel(Cycle - 1, ScanLine, GetColorFromPalette(Palette, Pixel));

	// render
	Cycle++;
	if (Cycle >= 341)
	{
		Cycle = 0;
		ScanLine++;

		if (ScanLine >= 261)
		{
			ScanLine = -1;
			FrameComplete = true;
		}
	}
}

uint8_t* PictureProcessor::GetOAMPointer()
{
	return POM;
}

PixelEngine::Pixel& PictureProcessor::GetColorFromPalette(uint8_t Palette, uint8_t Pixel)
{
	return PixelScreen[PpuRead(0x3F00 + (Palette << 2) + Pixel) & 0x3F];
}

PixelEngine::Sprite& PictureProcessor::GetScreen()
{
	return SpriteScreen;
}

PixelEngine::Sprite& PictureProcessor::GetNameTable(uint8_t i)
{
	return NameTable[i];
}

PixelEngine::Sprite& PictureProcessor::GetPatternTable(uint8_t i, uint8_t Palette)
{
	for (uint16_t TileY = 0; TileY < 16; ++TileY)
	{
		for (uint16_t TileX = 0; TileX < 16; ++TileX)
		{
			uint16_t Offset = TileY * 256 + TileX * 16;

			// Get Sprite
			for (uint16_t row = 0; row < 8; ++row)
			{
				// 앞 비트 뒷 비트
				uint8_t TileLSB = PpuRead(i * 0x1000 + Offset + row + 0);
				uint8_t TileMSB = PpuRead(i * 0x1000 + Offset + row + 8);

				for (uint16_t col = 0; col < 8; ++col)
				{
					uint8_t pixel = (TileLSB & 0x01) + (TileMSB & 0x01);
					TileMSB >>= 1;
					TileLSB >>= 1;

					PatternTable[i].SetPixel(
						TileX * 8 + (7 - col),
						TileY * 8 + row,
						GetColorFromPalette(Palette, pixel)
					);
				}

			}
		}
	}

	return PatternTable[i];
}
