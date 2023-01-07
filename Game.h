#ifndef GAME_H
#define GAME_H

enum class PlayerId { P1, P2 };

class Player 
{
public:
	Player(Player::PlayerId id, int startX, int startY);
	void Update();
	void Draw();
private:
	int x = 0, y = 0;
};

#endif // !GAME_H
