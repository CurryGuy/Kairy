/******************************************************************************
 *
 * Copyright (C) 2015 Nanni
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *****************************************************************************/

#include <Kairy/Tmx/TmxMapRenderer.h>
#include <Kairy/Graphics/RenderDevice.h>

NS_KAIRY_BEGIN

//=============================================================================

TmxMapRenderer::TmxMapRenderer(void)
	: Node()
	, _mapWidth(0)
	, _mapHeight(0)
	, _childsLayer(0)
	, _tileWidth(0)
	, _tileHeight(0)
	, _loaded(false)
	, _type(TmxMap::Orientation::Orthogonal)
{
	setCamera(Rect(0.0f, 0.0f, TOP_SCREEN_WIDTH, TOP_SCREEN_HEIGHT));
}

//=============================================================================

TmxMapRenderer::TmxMapRenderer(const TmxMap& map, Texture::Location location)
	: TmxMapRenderer()
{
	setMap(map, location);
}

//=============================================================================

TmxMapRenderer::~TmxMapRenderer()
{
}

//=============================================================================

void TmxMapRenderer::draw()
{
	for (int i = 0; i < getLayersCount(); ++i)
	{
		draw(i);
	}
}

//=============================================================================

void TmxMapRenderer::draw(int layerIndex)
{
	if (!_device->isInitialized() || !_visible ||
		!_loaded || layerIndex < 0 || layerIndex >= (int)_layers.size())
	{
		return;
	}

	updateTransform();

	if (_color.a > 0 && _type == TmxMap::Orientation::Orthogonal)
	{
		int startX = int(_camera.x) / _tileWidth;
		int startY = int(_camera.y) / _tileHeight;
		int offsX = int(_camera.x) % _tileWidth;
		int offsY = int(_camera.y) % _tileHeight;
		int width = int(_camera.width) / _tileWidth + 1 + (offsX ? 1 : 0);
		int height = int(_camera.height) / _tileHeight + 1 + (offsY ? 1 : 0);

		Layer& layer = _layers[layerIndex];

		if (_type == TmxMap::Orientation::Orthogonal)
		{
			for (int x = 0; x < width; ++x)
			{
				for (int y = 0; y < height; ++y)
				{
					int ix = x + startX;
					int iy = y + startY;

					if (ix < 0 || iy < 0 || ix >= _mapWidth || iy >= _mapHeight)
						continue;

					Tile& tile = layer.tiles[ix + iy * _mapWidth];

					if (tile.id < 0 || tile.tilesetIndex < 0 ||
						tile.tilesetIndex >= (int)_tilesets.size())
					{
						continue;
					}

					auto& tileset = _tilesets[tile.tilesetIndex];

					short id = getTileAnimId(tile);

					int srcX = (id % (tileset->columns - tileset->margin * 2 + tileset->spacing)) * tileset->tileWidth;
					int srcY = (id / (tileset->columns - tileset->margin * 2 + tileset->spacing)) * tileset->tileHeight;

					float screenX = float(x * _tileWidth - offsX);
					float screenY = float(y * _tileHeight - offsY);

					auto& sprite = tileset->sprite;

					sprite.setColor(_color);
					sprite.setOpacity(layer.opacity);
					sprite.setTextureRect(Rect((float)srcX, (float)srcY,
						(float)tileset->tileWidth, (float)tileset->tileHeight));
					sprite.setPosition(screenX, screenY);

					sprite.updateTransform();
					sprite.setTransform(getCombinedTransform() * sprite.getTransform());

					sprite.draw();
				}
			}
		}

	} /* _color.a > 0 */

	if (layerIndex == _childsLayer)
	{
		Node::draw();
	}
}

//=============================================================================

void TmxMapRenderer::update(float dt)
{
	Node::update(dt);

	for (auto& tileset : _tilesets)
	{
		for (auto& ait : tileset->animations)
		{
			Animation& animation = ait.second;

			animation.animTime += dt;

			if (animation.animTime >=
				animation.frames[animation.currentFrame].duration)
			{
				animation.currentFrame++;
				if (animation.currentFrame == animation.frames.size())
				{
					animation.currentFrame = 0;
				}
				animation.animTime = 0.0f;
			}
		}
	}
}

//=============================================================================

int TmxMapRenderer::getTileId(int layer, int x, int y) const
{
	if (layer < 0 || layer >= (int)_layers.size() ||
		x < 0 || y < 0 ||
		x >= _mapWidth || y >= _mapHeight)
	{
		return -1;
	}

	return _layers[layer].tiles[x + y * _mapWidth].id;
}

//=============================================================================

void TmxMapRenderer::setTileId(int layer, int x, int y, int id)
{
	if (layer < 0 || layer >= (int)_layers.size() ||
		x < 0 || y < 0 ||
		x >= _mapWidth || y >= _mapHeight)
	{
		return;
	}

	_layers[layer].tiles[x + y * _mapWidth].id = id;
}

//=============================================================================

short TmxMapRenderer::getTileAnimId(const Tile& tile)
{
	auto& tileset = _tilesets[tile.tilesetIndex];
	auto it = tileset->animations.find(tile.id);

	if (it != tileset->animations.end())
	{
		return it->second.frames[it->second.currentFrame].id;
	}

	return tile.id;
}

//=============================================================================

bool TmxMapRenderer::setMap(const TmxMap& map, Texture::Location location)
{
	_loaded = false;
	_mapWidth = 0;
	_mapHeight = 0;
	_tileWidth = 0;
	_tileHeight = 0;
	_layers.clear();
	_tilesets.clear();

	if (map.getWidth() == 0 || map.getHeight() == 0 ||
		map.getTileWidth() == 0 || map.getTileHeight() == 0 ||
		map.getTilesets().size() == 0 || map.getLayers().size() == 0)
	{
		return false;
	}

	_mapWidth = map.getWidth();
	_mapHeight = map.getHeight();
	_tileWidth = map.getTileWidth();
	_tileHeight = map.getTileHeight();

	// Loading tilesets
	_tilesets.resize(map.getTilesets().size());

	for (Uint32 t = 0; t < _tilesets.size(); ++t)
	{
		auto tileset = map.getTileset(t);
		_tilesets[t].reset(new Tileset());

		if (!_tilesets[t])
		{
			return false;
		}

		std::string path;

		if (tileset->getPath().length() > 0)
			path = tileset->getPath();
		else
			path = map.getPath();

		std::string filename = path + tileset->getImage().getFilename();

		if (!_tilesets[t]->sprite.loadTexture(filename, location))
		{
			return false;
		}

		_tilesets[t]->tileWidth = tileset->getTileWidth();
		_tilesets[t]->tileHeight = tileset->getTileHeight();
		_tilesets[t]->margin = tileset->getMargin();
		_tilesets[t]->spacing = tileset->getSpacing();
		_tilesets[t]->columns = _tilesets[t]->sprite.getTextureWidth() / _tilesets[t]->tileWidth;

		for (auto& tile : tileset->getTiles())
		{
			if (tile.getAnimation().getFrames().size() > 0)
			{
				short id = tile.getId();

				Animation animation;

				animation.animTime = 0.0f;
				animation.currentFrame = 0;

				for (auto& frame : tile.getAnimation().getFrames())
				{
					AnimationFrame animFrame;
					animFrame.duration = frame.getDuration() / 1000.0f;
					animFrame.id = frame.getId();

					animation.frames.push_back(animFrame);
				}

				_tilesets[t]->animations[id] = animation;
			}
		}
	}

	// Loading layers
	_layers.resize(map.getLayers().size());

	for (Uint32 l = 0; l < _layers.size(); ++l)
	{
		auto layer = map.getLayer(l);
		_layers[l].opacity = byte(layer->getOpacity() * (float)Color::OPAQUE);
		_layers[l].tiles.resize(layer->getTiles().size());

		for (Uint32 t = 0; t < _layers[l].tiles.size(); ++t)
		{
			_layers[l].tiles[t].id = layer->getTiles()[t].getId();
			_layers[l].tiles[t].tilesetIndex = layer->getTiles()[t].getTilesetIndex();
		}
	}

	setSize(Vec2(
		(float)getMapWidthInPixels(),
		(float)getMapHeightInPixels()));

	_type = map.getOrientation();
	_loaded = true;

	return true;
}

//=============================================================================

NS_KAIRY_END
