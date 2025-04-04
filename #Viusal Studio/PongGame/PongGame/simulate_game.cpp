#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

float player_1_p, player_1_dp, player_2_p, player_2_dp;
float arena_half_size_x = 89, arena_half_size_y = 46;
float player_half_size_x = 1.5, player_half_size_y = 8;
float ball_p_x, ball_p_y, ball_dp_x = 100, ball_dp_y, ball_half_size = 2;

int p1_score = 0, p2_score = 0;

internal void simulate_player(float* p, float* dp, float ddp, float dt) {
	ddp -= *dp * 10.f;

	*p = *p + *dp * dt + ddp * dt * dt * .5f;
	*dp = *dp + ddp * dt;

	if (*p + player_half_size_y > arena_half_size_y) {
		*p = arena_half_size_y - player_half_size_y;
		*dp = 0;
	}
	else if (*p - player_half_size_y < -arena_half_size_y) {
		*p = -arena_half_size_y + player_half_size_y;
		*dp = 0;
	}
}

internal bool aabb_vs_aabb(float p1x, float p1y, float hs1x, float hs1y,
	float p2x, float p2y, float hs2x, float hs2y) {
	
	return (p1x + hs1x > p2x - hs2x &&
		p1x - hs1x < p2x + hs2x &&
		p1y + hs1y > p2y - hs2y &&
		p1y + hs1y < p2y + hs2y);
}

enum Gamemode {
	GM_MENU,
	GM_GAMEPLAY,
};

Gamemode current_gamemode;
int menu_select = 0;

internal void simulate_game(Input* input, float dt) {
	clear_screen(0x000000);
	draw_rect(0, 0, arena_half_size_x, arena_half_size_y, 0xffffff);
	draw_rect(0, 0, 88, 45, 0x0d6625);

	if (current_gamemode == GM_GAMEPLAY) {
		draw_rect(0, 18, .1, 6, 0xffffff);
		draw_rect(0, 36, .1, 6, 0xffffff);
		draw_rect(0, 0, .1, 6, 0xffffff);
		draw_rect(0, -18, .1, 6, 0xffffff);
		draw_rect(0, -36, .1, 6, 0xffffff);

		if (pressed(BUTTON_ESCAPE)) current_gamemode = GM_MENU;

		float player_1_ddp = 0.f;

		if (menu_select == 1) {
			if (is_down(BUTTON_UP)) player_1_ddp += 2000;
			if (is_down(BUTTON_DOWN)) player_1_ddp -= 2000;
		}
		else {
			if (ball_p_y > player_1_p+2.f) player_1_ddp += 1350;
			if (ball_p_y < player_1_p-2.f) player_1_ddp -= 1350;
			/*
			player_1_ddp = (ball_p_y - player_1_ddp) * 100;
			if (player_1_ddp > 1300) player_1_ddp = 1300;
			if (player_1_ddp < -1300) player_1_ddp = -1300;
			*/
		}	

		float player_2_ddp = 0.f;
		if (is_down(BUTTON_W)) player_2_ddp += 2000;
		if (is_down(BUTTON_S)) player_2_ddp -= 2000;

		simulate_player(&player_1_p, &player_1_dp, player_1_ddp, dt);
		simulate_player(&player_2_p, &player_2_dp, player_2_ddp, dt);

		// Simulate Ball
		{
			ball_p_x += ball_dp_x * dt;
			ball_p_y += ball_dp_y * dt;

			if (aabb_vs_aabb(ball_p_x, ball_p_y, ball_half_size, ball_half_size, 80, player_1_p, player_half_size_x, player_half_size_y)) {
				ball_p_x = 80 - player_half_size_x - ball_half_size;
				ball_dp_x *= -1;
				ball_dp_y = (ball_p_y - player_1_p) * 2 + player_1_dp * .75f;
			}
			else if (aabb_vs_aabb(ball_p_x, ball_p_y, ball_half_size, ball_half_size, -80, player_2_p, player_half_size_x, player_half_size_y)) {
				ball_p_x = -80 + player_half_size_x + ball_half_size;
				ball_dp_x *= -1;
				ball_dp_y = (ball_p_y - player_2_p) * 2 + player_2_dp * .75f;
			}

			if (ball_p_y + ball_half_size > arena_half_size_y) {
				ball_p_y = arena_half_size_y - ball_half_size;
				ball_dp_y *= -1;
			}
			else if (ball_p_y - ball_half_size < -arena_half_size_y) {
				ball_p_y = -arena_half_size_y + ball_half_size;
				ball_dp_y *= -1;
			}

			if (ball_p_x - ball_half_size > arena_half_size_x) {
				ball_dp_x *= -1;
				ball_dp_y = 0;
				ball_p_x = 0;
				ball_p_y = 0;
				p1_score++;
			}
			else if (ball_p_x - ball_half_size < -arena_half_size_x) {
				ball_dp_x *= -1;
				ball_dp_y = 0;
				ball_p_x = 0;
				ball_p_y = 0;
				p2_score++;
			}
		}

		draw_number(p1_score, -10, 40, 1.f, 0xbbffbb);
		draw_number(p2_score, 10, 40, 1.f, 0xbbffbb);

		// Rendering
		draw_rect(ball_p_x, ball_p_y, ball_half_size, ball_half_size, 0xff780a);

		draw_rect(80, player_1_p, player_half_size_x, player_half_size_y, 0xffffff);
		draw_rect(-80, player_2_p, player_half_size_x, player_half_size_y, 0xffffff);
	}
	else {

		if (pressed(BUTTON_LEFT)) menu_select = 0;
		if (pressed(BUTTON_RIGHT)) menu_select = 1;
		if (pressed(BUTTON_DOWN)) menu_select = 2;
		if (pressed(BUTTON_UP)) menu_select = 0;
		if (pressed(BUTTON_ENTER) && (menu_select == 1 || menu_select == 0)) current_gamemode = GM_GAMEPLAY;
		else if (pressed(BUTTON_ENTER) && menu_select == 2) running = false;
		if (pressed(BUTTON_ESCAPE)) running = false;

		if (menu_select == 0) {
			draw_rect(-15, 0, 10, 10, 0xffffff);
			draw_rect(15, 0, 10, 10, 0x09471a);
			draw_text("SINGLE", -23, 5, .5f, 0x000000);
			draw_text("PLAYER", -23, -2, .5f, 0x000000);
			draw_text("MULI", 10, 5, .5f, 0x04240d);
			draw_text("PLAYER", 7, -2, .5f, 0x04240d);

			draw_rect(0, -23, 25, 7, 0x3d1313);
			draw_text("EXIT", -8, -21, .8f, 0x260c0c);
		}
		else if(menu_select == 1){
			draw_rect(15, 0, 10, 10, 0xffffff);
			draw_rect(-15, 0, 10, 10, 0x09471a);
			draw_text("SINGLE", -23, 5, .5f, 0x04240d);
			draw_text("PLAYER", -23, -2, .5f, 0x04240d);
			draw_text("MULI", 10, 5, .5f, 0x000000);
			draw_text("PLAYER", 7, -2, .5f, 0x000000);

			draw_rect(0, -23, 25, 7, 0x3d1313);
			draw_text("EXIT", -8, -21, .8f, 0x260c0c);
		}
		else {
			draw_rect(15, 0, 10, 10, 0x09471a);
			draw_rect(-15, 0, 10, 10, 0x09471a);
			draw_text("SINGLE", -23, 5, .5f, 0x000000);
			draw_text("PLAYER", -23, -2, .5f, 0x000000);
			draw_text("MULI", 10, 5, .5f, 0x000000);
			draw_text("PLAYER", 7, -2, .5f, 0x000000);

			draw_rect(0, -23, 25, 7, 0x6b1e1e);
			draw_text("EXIT", -8, -21, .8f, 0x962f2f);
		}
	}

}