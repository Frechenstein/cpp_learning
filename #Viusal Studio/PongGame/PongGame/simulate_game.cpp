#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

float player_pos_y = 0.f;

internal void simulate_game(Input* input, float dt) {
	clear_screen(0x000000);
	draw_rect(0, 0, 89, 46, 0xffffff);
	draw_rect(0, 0, 88, 45, 0x0d6625);

	draw_rect(0, 18, .1, 6, 0xffffff);
	draw_rect(0, 36, .1, 6, 0xffffff);
	draw_rect(0, 0, .1, 6, 0xffffff);
	draw_rect(0, -18, .1, 6, 0xffffff);
	draw_rect(0, -36, .1, 6, 0xffffff);

	float speed = 50.f;
	if (is_down(BUTTON_UP)) player_pos_y += speed * dt;
	if (is_down(BUTTON_DOWN)) player_pos_y -= speed * dt;

	draw_rect(80, player_pos_y, 1.5, 8, 0xffffff);
	draw_rect(-80, 0, 1.5, 8, 0xffffff);

	draw_rect(0, 0, 2, 2, 0xff780a);
}