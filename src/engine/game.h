/*
 * Copyright (C) 2023, A. Roldán. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GAME_H
#define GAME_H

#include <map>
#include "map.h"
#include "player.h"
#include "hud.h"
#include "hocus.h"
#include "data/asset/iteminfo.h"
#include "fade.h"
#include "particles.h"

namespace pocus {

class Game {
public:
	enum { PLAYER_MAX_HEALTH = 100 };
	enum { DEFAULT_TEXT_COLOR = 104 };
	enum { SCORE_TEXT_LIFETIME = 1000 };
	
public:
	Game();
	
	Map& getMap();
	Player& getPlayer();
	Hud& getHud();
	data::asset::Palette& getPalette();
	data::asset::Font& getFont();
	Point& getOffset();
	Hocus& getHocus();
	Size& getViewportSize();
	data::asset::ItemInfo& getItemInfo();
	std::map<uint32_t, std::unique_ptr<Texture>>& getScoreTextures();
	std::vector<std::unique_ptr<Texture>>& getHintTextures();
	std::unique_ptr<Sound>& getSoundHint();
	std::unique_ptr<Sound>& getSoundCrystal();
	std::unique_ptr<Sound>& getSoundSpecialItem();
	std::unique_ptr<Sound>& getSoundPotion();
	std::unique_ptr<Sound>& getSoundHit();
	std::vector<std::unique_ptr<Sound>>& getSoundsItem();
	std::unique_ptr<Sound>& getSoundShot();
	//std::vector<std::unique_ptr<Texture>>& getProjectileTextures();
	
	void addScoreText(Texture& texture, const Point& point);
	
	void setTextColor(uint8_t color);
	
	void start();
	void render(Renderer& renderer);
	void update(float dt);
	
	//uint32_t getElapsedTime();
	
	void addScore(uint32_t score);
	void removeHealth(uint8_t health);
	void addHealth(uint8_t health);
	void addSilverKey();
	void removeSilverKey();
	void addGoldenKey();
	void removeGoldenKey();
	void togglePause();
	void startMovement(const Entity::Direction_t& direction);
	void stopMovement(const Entity::Direction_t& direction);
	void addCrystal(uint32_t amount);
	void jump();
	void showHint(uint32_t id);
	void hideHint();
	void activate();
	void hurt(uint8_t health);
	void startShooting();
	void stopShooting();
	void shoot();
	void updateProjectiles(float dt);
	void addFirePower(uint8_t power = 1);
	
private:
	Size viewportSize { 320.0f, 200.0f };
	data::asset::Font font;
	data::asset::Palette palette;
	uint8_t textColor { DEFAULT_TEXT_COLOR };
	Point offset;
	Map map;
	Player player;
	Hud hud;
	Tick tickStart;
	bool paused { false };
	std::unique_ptr<Texture> labelPaused;
	Hocus hocus;
	data::asset::ItemInfo itemInfo;
	std::map<uint32_t, std::unique_ptr<Texture>> scoreTextures;
	std::vector<Entity> scoreTexts;
	std::vector<std::unique_ptr<Texture>> hintTextures;
	int currentHint { -1 };
	std::unique_ptr<Sound> soundHint, soundCrystal, soundPotion, soundHit, soundSpecialItem;
	std::vector<std::unique_ptr<Sound>> soundsItem;
	std::unique_ptr<Sound> soundShot;
	Fade fadeCrystal;
	//std::vector<std::unique_ptr<Texture>> projectileTextures;
	std::vector<Projectile> projectiles;

	void move(float dt);
	void checkItems();
	void checkHazards();
	void centerCamera(const Hocus& hocus, const Size& viewportSize);
	bool isShowingHint() const;
	void createProjectile(const Entity& source);
};

}

#endif // GAME_H
