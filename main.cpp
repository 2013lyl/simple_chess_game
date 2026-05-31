#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <vector>
#include <array>
#include <chrono>
#include <string>
#include <sstream>
#include "sprites.cpp"
#include "tools.cpp"

using namespace std;

auto last_left_click_time = chrono::steady_clock::now();
auto last_right_click_time = chrono::steady_clock::now();
const int LEFT_CLICK_COOLDOWN_MS = 200;
const int RIGHT_CLICK_COOLDOWN_MS = 200;

int WIDTH, HEIGHT;
int UIWIDTH, UIHEIGHT;
int BOARDWIDTH, BOARDHEIGHT, GRIDWIDTH, GRIDHEIGHT;
int CIRCLEWIDTH, CIRCLEHEIGHT; //圆圈指示的长宽

IMAGE soldier_black_img, soldier_black_mask_img;
IMAGE king_black_img, king_black_mask_img;
IMAGE queen_black_img, queen_black_mask_img;
IMAGE bishop_black_img, bishop_black_mask_img;
IMAGE knight_black_img, knight_black_mask_img;
IMAGE rook_black_img, rook_black_mask_img;
IMAGE soldier_white_img, soldier_white_mask_img;
IMAGE king_white_img, king_white_mask_img;
IMAGE queen_white_img, queen_white_mask_img;
IMAGE bishop_white_img, bishop_white_mask_img;
IMAGE knight_white_img, knight_white_mask_img;
IMAGE rook_white_img, rook_white_mask_img;

IMAGE path_circle_img, attack_circle_img, path_circle_mask_img, attack_circle_mask_img;

string now_round = "white";

string pieces_layout_lst[] = {"rook", "knight", "bishop", "queen", "king", "bishop", "knight", "rook"};

vector<Piece> pieces_group;
vector<Circle> circles_group;

vector<vector<string>> board_pieces_lst;

vector<IMAGE*> name_to_piece_images(string piece_name, string side){
	vector<IMAGE*> ans;
	if (side == "black"){
		if (piece_name == "rook"){
			ans.push_back(&rook_black_img);
			ans.push_back(&rook_black_mask_img);
			return ans;
		}
		else if (piece_name == "knight"){
			ans.push_back(&knight_black_img);
			ans.push_back(&knight_black_mask_img);
			return ans;
		}
		else if (piece_name == "bishop"){
			ans.push_back(&bishop_black_img);
			ans.push_back(&bishop_black_mask_img);
			return ans;
		}
		else if (piece_name == "queen"){
			ans.push_back(&queen_black_img);
			ans.push_back(&queen_black_mask_img);
			return ans;
		}
		else if (piece_name == "king"){
			ans.push_back(&king_black_img);
			ans.push_back(&king_black_mask_img);
			return ans;
		}
		else if (piece_name == "soldier"){
			ans.push_back(&soldier_black_img);
			ans.push_back(&soldier_black_mask_img);
			return ans;
		}
	}
	else if (side == "white"){
		if (piece_name == "soldier"){
			ans.push_back(&soldier_white_img);
			ans.push_back(&soldier_white_mask_img);
			return ans;
		}
		else if (piece_name == "knight"){
			ans.push_back(&knight_white_img);
			ans.push_back(&knight_white_mask_img);
			return ans;
		}
		else if (piece_name == "bishop"){
			ans.push_back(&bishop_white_img);
			ans.push_back(&bishop_white_mask_img);
			return ans;
		}
		else if (piece_name == "queen"){
			ans.push_back(&queen_white_img);
			ans.push_back(&queen_white_mask_img);
			return ans;
		}
		else if (piece_name == "king"){
			ans.push_back(&king_white_img);
			ans.push_back(&king_white_mask_img);
			return ans;
		}
		else if (piece_name == "rook"){
			ans.push_back(&rook_white_img);
			ans.push_back(&rook_white_mask_img);
			return ans;
		}
	}

	return ans;
}

void load_image(){
	// 加载黑方图片
	// 加载兵的图片
	loadimage(&soldier_black_img, "pic/pieces/black/soldier.png", GRIDWIDTH, GRIDHEIGHT, true);
	loadimage(&soldier_black_mask_img, "pic/pieces/black/soldier_mask.png", GRIDWIDTH, GRIDHEIGHT, true);

	// 加载王的图片
	loadimage(&king_black_img, "pic/pieces/black/king.png", GRIDWIDTH, GRIDHEIGHT, true);
	loadimage(&king_black_mask_img, "pic/pieces/black/king_mask.png", GRIDWIDTH, GRIDHEIGHT, true);

	// 加载王后的图片
	loadimage(&queen_black_img, "pic/pieces/black/queen.png", GRIDWIDTH, GRIDHEIGHT, true);
	loadimage(&queen_black_mask_img, "pic/pieces/black/queen_mask.png", GRIDWIDTH, GRIDHEIGHT, true);

	// 加载象的图片
	loadimage(&bishop_black_img, "pic/pieces/black/bishop.png", GRIDWIDTH, GRIDHEIGHT, true);
	loadimage(&bishop_black_mask_img, "pic/pieces/black/bishop_mask.png", GRIDWIDTH, GRIDHEIGHT, true);

	// 加载马的图片
	loadimage(&knight_black_img, "pic/pieces/black/knight.png", GRIDWIDTH, GRIDHEIGHT, true);
	loadimage(&knight_black_mask_img, "pic/pieces/black/knight_mask.png", GRIDWIDTH, GRIDHEIGHT, true);

	// 加载车的图片
	loadimage(&rook_black_img, "pic/pieces/black/rook.png", GRIDWIDTH, GRIDHEIGHT, true);
	loadimage(&rook_black_mask_img, "pic/pieces/black/rook_mask.png", GRIDWIDTH, GRIDHEIGHT, true);

	// 加载白方图片
	// 加载兵的图片
	loadimage(&soldier_white_img, "pic/pieces/white/soldier.png", GRIDWIDTH, GRIDHEIGHT, true);
	loadimage(&soldier_white_mask_img, "pic/pieces/white/soldier_mask.png", GRIDWIDTH, GRIDHEIGHT, true);

	// 加载王的图片
	loadimage(&king_white_img, "pic/pieces/white/king.png", GRIDWIDTH, GRIDHEIGHT, true);
	loadimage(&king_white_mask_img, "pic/pieces/white/king_mask.png", GRIDWIDTH, GRIDHEIGHT, true);

	// 加载王后的图片
	loadimage(&queen_white_img, "pic/pieces/white/queen.png", GRIDWIDTH, GRIDHEIGHT, true);
	loadimage(&queen_white_mask_img, "pic/pieces/white/queen_mask.png", GRIDWIDTH, GRIDHEIGHT, true);

	// 加载象的图片
	loadimage(&bishop_white_img, "pic/pieces/white/bishop.png", GRIDWIDTH, GRIDHEIGHT, true);
	loadimage(&bishop_white_mask_img, "pic/pieces/white/bishop_mask.png", GRIDWIDTH, GRIDHEIGHT, true);

	// 加载车的图片
	loadimage(&rook_white_img, "pic/pieces/white/rook.png", GRIDWIDTH, GRIDHEIGHT, true);
	loadimage(&rook_white_mask_img, "pic/pieces/white/rook_mask.png", GRIDWIDTH, GRIDHEIGHT, true);

	// 加载马的图片
	loadimage(&knight_white_img, "pic/pieces/white/knight.png", GRIDWIDTH, GRIDHEIGHT, true);
	loadimage(&knight_white_mask_img, "pic/pieces/white/knight_mask.png", GRIDWIDTH, GRIDHEIGHT, true);

	
	// 加载 路径 攻击 指示图片
	loadimage(&path_circle_img, "pic/path_circle.png", CIRCLEWIDTH, CIRCLEHEIGHT, true);
	loadimage(&attack_circle_img, "pic/attack_circle.png", CIRCLEWIDTH, CIRCLEHEIGHT, true);
	loadimage(&path_circle_mask_img, "pic/path_circle_mask.png", CIRCLEWIDTH, CIRCLEHEIGHT, true);
	loadimage(&attack_circle_mask_img, "pic/attack_circle_mask.png", CIRCLEWIDTH, CIRCLEHEIGHT, true);
}

void init(){
	WIDTH = 1200;
	HEIGHT = 800;
	BOARDWIDTH = 8;
	BOARDHEIGHT = 8;
	UIWIDTH = 400;
	UIHEIGHT = 800;
	GRIDWIDTH = (WIDTH - UIWIDTH) / BOARDWIDTH;
	GRIDHEIGHT = HEIGHT / BOARDHEIGHT;
	CIRCLEWIDTH = GRIDWIDTH * 1 / 5;
	CIRCLEHEIGHT = CIRCLEWIDTH;

	now_round = "white";

	load_image();

	pieces_group.clear();
	circles_group.clear();

	board_pieces_lst.clear();
	for (int r=0;r<BOARDHEIGHT;r++){
		vector<string> new_vector = {};
		board_pieces_lst.push_back(new_vector);
		for (int c=0;c<BOARDWIDTH;c++){
			board_pieces_lst[r].push_back("empty");
		}
	}
}

void create_pieces(){
	int id=0;
	for (size_t i=0;i<sizeof(pieces_layout_lst) / sizeof(pieces_layout_lst[0]); i++){
		vector<IMAGE*> piece_images = name_to_piece_images(pieces_layout_lst[i], "black");
		string piece_name = pieces_layout_lst[i] + "-black";
		if (piece_images.size() == 2){
			Piece new_piece(piece_images[0], piece_images[1], i*GRIDWIDTH, 0, i, 0, GRIDWIDTH, GRIDHEIGHT, piece_name, id);
			pieces_group.push_back(new_piece);
			board_pieces_lst[0][i] = piece_name;
		}
		id++;
	}
	for (size_t i=0;i<sizeof(pieces_layout_lst) / sizeof(pieces_layout_lst[0]); i++){
		vector<IMAGE*> piece_images = name_to_piece_images("soldier", "black");
		string piece_name = "soldier-black";
		if (piece_images.size() == 2){
			Piece new_piece(piece_images[0], piece_images[1], i*GRIDWIDTH, GRIDHEIGHT, i, 1, GRIDWIDTH, GRIDHEIGHT, piece_name, id);
			pieces_group.push_back(new_piece);
			board_pieces_lst[1][i] = piece_name;
		}
		id++;
	}

	for (size_t i=0;i<sizeof(pieces_layout_lst) / sizeof(pieces_layout_lst[0]); i++){
		vector<IMAGE*> piece_images = name_to_piece_images(pieces_layout_lst[i], "white");
		string piece_name = pieces_layout_lst[i] + "-white";
		if (piece_images.size() == 2){
			Piece new_piece(piece_images[0], piece_images[1], i*GRIDWIDTH, HEIGHT - GRIDHEIGHT, i, BOARDHEIGHT-1, GRIDWIDTH, GRIDHEIGHT, piece_name, id);
			pieces_group.push_back(new_piece);
			board_pieces_lst[BOARDHEIGHT-1][i] = piece_name;
		}
		id++;
	}
	for (size_t i=0;i<sizeof(pieces_layout_lst) / sizeof(pieces_layout_lst[0]); i++){
		vector<IMAGE*> piece_images = name_to_piece_images("soldier", "white");
		string piece_name = "soldier-white";
		if (piece_images.size() == 2){
			Piece new_piece(piece_images[0], piece_images[1], i*GRIDWIDTH, HEIGHT - GRIDHEIGHT * 2, i, BOARDHEIGHT - 2 ,GRIDWIDTH, GRIDHEIGHT, piece_name, id);
			pieces_group.push_back(new_piece);
			board_pieces_lst[BOARDHEIGHT-2][i] = piece_name;
		}
		id++;
	}
}

void draw_board(){
	for (int r=0;r<BOARDWIDTH;r++){
		for (int c=0;c<BOARDHEIGHT;c++){
			if ((r + c) % 2 == 0){
				setfillcolor(RGB(20, 20, 20));
			}
			else{
				setfillcolor(RGB(200, 200, 200));
			}			
			setcolor(BLACK);
			fillrectangle(r*GRIDWIDTH, c*GRIDHEIGHT, (r+1)*GRIDWIDTH, (c+1)*GRIDHEIGHT);
		}
	}	
}

int main(){
	init();

	initgraph(WIDTH, HEIGHT);

	setbkcolor(WHITE);
	cleardevice();

	draw_board();

	create_pieces();	

	for (size_t i=0;i<pieces_group.size();i++){
		cout << pieces_group[i].id << " ";
		pieces_group[i].is_clicked = false;
	}

	MOUSEMSG mmsg;

	while (true) {
		if (MouseHit()){
			mmsg = GetMouseMsg();

			// 棋子的点击效果显示逻辑
			if (mmsg.uMsg == WM_LBUTTONDOWN){
				auto current_time = std::chrono::steady_clock::now();
				auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_left_click_time).count();

				circles_group.clear();

				if (elapsed >= LEFT_CLICK_COOLDOWN_MS){
					last_left_click_time = current_time;

					// 计算鼠标点击的格子位置
					int mouse_x = mmsg.x;
					int mouse_y = mmsg.y;
					int mouse_grid_x = mouse_x / GRIDWIDTH;
					int mouse_grid_y = mouse_y / GRIDHEIGHT;

					int click_piece_index = -1;

					for (size_t i=0;i<pieces_group.size();i++){	
						if (pieces_group[i].grid_x == mouse_grid_x && pieces_group[i].grid_y == mouse_grid_y){
							click_piece_index = i;
							break;
						}
					}

					if (click_piece_index != -1){
						if (pieces_group[click_piece_index].is_clicked){
							pieces_group[click_piece_index].is_clicked = false;
						}
						else{
							for (size_t j=0;j<pieces_group.size();j++){
								pieces_group[j].is_clicked = false;
							}

							pieces_group[click_piece_index].is_clicked = true;
						}
					}
					else{
						for (size_t j=0;j<pieces_group.size();j++){
							pieces_group[j].is_clicked = false;
						}
					}
				}
			}
				
			
			// 路径的点击逻辑
			if (mmsg.uMsg == WM_RBUTTONDOWN){	
				auto current_time = std::chrono::steady_clock::now();
				auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_right_click_time).count();
				
				if (elapsed >= RIGHT_CLICK_COOLDOWN_MS){
					last_right_click_time = current_time;

					// 计算鼠标点击的格子位置
					int mouse_x = mmsg.x;
					int mouse_y = mmsg.y;
					int mouse_grid_x = mouse_x / GRIDWIDTH;
					int mouse_grid_y = mouse_y / GRIDHEIGHT;

					for (size_t i=0;i<circles_group.size();i++){
						if (circles_group[i].grid_x == mouse_grid_x && circles_group[i].grid_y == mouse_grid_y){
							if (circles_group[i].circle_kind == "path"){
								// 找到指定id的棋子
								Piece* piece;
								for (size_t a=0;a<pieces_group.size();a++){
									if (pieces_group[a].id == circles_group[i].piece_id){
										piece = &pieces_group[a];
									}
								}
								string piece_name = piece->name; 
								board_pieces_lst[piece->grid_y][piece->grid_x] = "empty";

								piece->grid_x = circles_group[i].grid_x;
								piece->grid_y = circles_group[i].grid_y;
								piece->x = circles_group[i].grid_x * GRIDWIDTH;
								piece->y = circles_group[i].grid_y * GRIDHEIGHT;
								piece->is_clicked = false;
							
								board_pieces_lst[circles_group[i].grid_y][circles_group[i].grid_x] = piece_name;

								break;
							}
							else if (circles_group[i].circle_kind == "attack") {
   								int attacker_id = circles_group[i].piece_id;
    							int new_x = circles_group[i].grid_x;
    							int new_y = circles_group[i].grid_y;
    
    							// 删除被攻击的棋子
    							for (auto it = pieces_group.begin(); it != pieces_group.end(); ++it) {
        							if (it->grid_x == new_x && it->grid_y == new_y) {
            							pieces_group.erase(it);
            							break;
        							}
    							}
    
    							// 通过 ID 查找攻击者
    							for (auto& p : pieces_group) {
        							if (p.id == attacker_id) {
            							// 移动棋子
            							board_pieces_lst[p.grid_y][p.grid_x] = "empty";
            							p.grid_x = new_x;
            							p.grid_y = new_y;
            							p.x = new_x * GRIDWIDTH;
            							p.y = new_y * GRIDHEIGHT;
        								p.is_clicked = false;
            							board_pieces_lst[new_y][new_x] = p.name;
            							break;
       								}
    							}
   							}		
						}
					}

					if (now_round == "white"){
						now_round = "black";
					}
					else {
						now_round = "white";
					}

					circles_group.clear();
				}
			}	
		}

		BeginBatchDraw();
		cleardevice();
		draw_board();

		settextstyle(30, 0, _T("微软雅黑"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(BOARDWIDTH * GRIDWIDTH, 10, ("Now round:" + now_round).c_str());

		circles_group.clear();

		for (size_t i=0;i<pieces_group.size();i++){
			pieces_group[i].draw();

			// 显示圆圈指示
			if (pieces_group[i].is_clicked){
				vector<string> piece_name_lst = split(pieces_group[i].name, '-');
				string piece_name = piece_name_lst[0];
				string piece_side = piece_name_lst[1];

				int piece_grid_x = pieces_group[i].grid_x;
				int piece_grid_y = pieces_group[i].grid_y;

				vector<pair<int, int>> path_pos_lst;
				vector<pair<int, int>> attack_pos_lst;

				if (piece_side != now_round){
					continue;
				}

				if (piece_name == "soldier"){
					if (piece_side == "black"){
						// 检测路径
						if (pieces_group[i].grid_y == 1){
							// 可以向前走两格或者一格
							// 检测前面一个是否有棋子
							if (board_pieces_lst[piece_grid_y+1][piece_grid_x] == "empty"){
								path_pos_lst.push_back(make_pair(piece_grid_y+1, piece_grid_x));
								// 检测前面2格是否有棋子
								if (board_pieces_lst[piece_grid_y+2][piece_grid_x] == "empty"){
									path_pos_lst.push_back(make_pair(piece_grid_y+2, piece_grid_x));
								}
							}
						}
						else{
							// 检测前面是否有棋子
							if (piece_grid_y+1<=BOARDHEIGHT-1){
								if (board_pieces_lst[piece_grid_y+1][piece_grid_x] == "empty"){
									path_pos_lst.push_back(make_pair(piece_grid_y+1, piece_grid_x));
								}
							}
							
						}
						// 检测吃子
						// 右上方
						if (piece_grid_y+1 <= BOARDHEIGHT-1){
							if (piece_grid_x >= 1 && piece_grid_x <= BOARDWIDTH - 2){
								if (board_pieces_lst[piece_grid_y+1][piece_grid_x+1] != "empty"){
									// 检测是否是对方棋子
									if (split(board_pieces_lst[piece_grid_y+1][piece_grid_x+1], '-')[1] == "white"){
										attack_pos_lst.push_back(make_pair(piece_grid_y+1, piece_grid_x+1));
									}
								}
								// 左上方
								if (board_pieces_lst[piece_grid_y+1][piece_grid_x-1] != "empty"){
									if (split(board_pieces_lst[piece_grid_y+1][piece_grid_x-1], '-')[1] == "white"){
										attack_pos_lst.push_back(make_pair(piece_grid_y+1, piece_grid_x-1));
									}
							
								}
							}
							
						}
					}
					if (piece_side == "white"){
						if (pieces_group[i].grid_y == BOARDHEIGHT-2){
							// 可以向前走两格或者一格
							// 检测前面一个是否有棋子
							if (board_pieces_lst[piece_grid_y-1][piece_grid_x] == "empty"){
								path_pos_lst.push_back(make_pair(piece_grid_y-1, piece_grid_x));
								// 检测前面2格是否有棋子
								if (board_pieces_lst[piece_grid_y-2][piece_grid_x] == "empty"){
									path_pos_lst.push_back(make_pair(piece_grid_y-2, piece_grid_x));
								}
							}
						}
						else{
							// 检测前面是否有棋子
							if (piece_grid_y-1>=0){
								if (board_pieces_lst[piece_grid_y-1][piece_grid_x] == "empty"){
									path_pos_lst.push_back(make_pair(piece_grid_y-1, piece_grid_x));
								}
							}
						}
						// 检测吃子
						// 右上方
						if (piece_grid_y-1>=0){
							if (piece_grid_x >= 1 && piece_grid_x <= BOARDWIDTH - 2){
								if (board_pieces_lst[piece_grid_y-1][piece_grid_x+1] != "empty"){
									// 检测是否是对方棋子
									if (split(board_pieces_lst[piece_grid_y-1][piece_grid_x+1], '-')[1] == "black"){
										attack_pos_lst.push_back(make_pair(piece_grid_y-1, piece_grid_x+1));
									}
								}
								// 左上方
								if (board_pieces_lst[piece_grid_y-1][piece_grid_x-1] != "empty"){
									if (split(board_pieces_lst[piece_grid_y-1][piece_grid_x-1], '-')[1] == "black"){
										attack_pos_lst.push_back(make_pair(piece_grid_y-1, piece_grid_x-1));
									}
								}
							}
						}
						
					}
				}

				
				else if (piece_name == "knight") {
					// 马的所有可能移动位置 (行, 列) 偏移量
					int knight_moves[8][2] = {{-2, -1}, {-2, 1},{-1, -2}, {-1, 2},{1, -2}, {1, 2},{2, -1}, {2, 1}};
    
    				for (int k = 0; k < 8; k++) {
						int new_row = piece_grid_y + knight_moves[k][0];
						int new_col = piece_grid_x + knight_moves[k][1];
						
						// 边界检查
						if (new_row >= 0 && new_row < BOARDHEIGHT && 
    						new_col >= 0 && new_col < BOARDWIDTH) {
							
							string target = board_pieces_lst[new_row][new_col];
							
							if (target == "empty") {
								// 空位：可走路径
								path_pos_lst.push_back(make_pair(new_row, new_col));
							} else {
								// 有棋子：检查是否是敌方棋子
								vector<string> target_lst = split(target, '-');
								if (target_lst.size() >= 2 && target_lst[1] != piece_side) {
									// 敌方棋子：攻击路径
									attack_pos_lst.push_back(make_pair(new_row, new_col));
								}
							}
						}
    				}
				}
				else if (piece_name == "bishop"){
					pair<int, int> directions[4] = {
						make_pair(-1, -1),
						make_pair(-1, 1),
						make_pair(1, -1),
						make_pair(1, 1)
					};
					for (int c=0;c<4;c++){
						bool is_check = true;
						int now_piece_grid_y = piece_grid_y;
						int now_piece_grid_x = piece_grid_x;
						while (is_check){
							now_piece_grid_y += directions[c].first;
							now_piece_grid_x += directions[c].second;
							if (now_piece_grid_y >= 0 && now_piece_grid_y <= BOARDHEIGHT-1 && now_piece_grid_x >= 0 && now_piece_grid_x <= BOARDWIDTH-1){
								if (board_pieces_lst[now_piece_grid_y][now_piece_grid_x] == "empty"){
									path_pos_lst.push_back(make_pair(now_piece_grid_y, now_piece_grid_x));
								}
								else{
									if (split(board_pieces_lst[now_piece_grid_y][now_piece_grid_x], '-')[1] != piece_side){
										attack_pos_lst.push_back(make_pair(now_piece_grid_y, now_piece_grid_x));
									}
									is_check = false;
								}
							}
							else{
								is_check = false;
							}
						}
					}
				}
				else if (piece_name == "rook"){
					pair<int, int> directions[4] = {
						make_pair(1, 0),
						make_pair(-1, 0),
						make_pair(0, 1),
						make_pair(0, -1)
					};

					for (int c=0;c<4;c++){
						bool is_check = true;
						int now_piece_grid_y = piece_grid_y;
						int now_piece_grid_x = piece_grid_x;
						while (is_check){
							now_piece_grid_y += directions[c].first;
							now_piece_grid_x += directions[c].second;

							if (now_piece_grid_y >= 0 && now_piece_grid_y <= BOARDHEIGHT-1 && now_piece_grid_x >= 0 && now_piece_grid_x <= BOARDWIDTH-1){
								if (board_pieces_lst[now_piece_grid_y][now_piece_grid_x] == "empty"){
									path_pos_lst.push_back(make_pair(now_piece_grid_y, now_piece_grid_x));	
								}
								else{
									if (split(board_pieces_lst[now_piece_grid_y][now_piece_grid_x], '-')[1] != piece_side){
										attack_pos_lst.push_back(make_pair(now_piece_grid_y, now_piece_grid_x));
									}
									is_check = false;

								}
							}
							else{
								is_check = false;
							}
						}
					}
				}

				else if (piece_name == "queen"){
					pair<int, int> directions[8] = {
						make_pair(0, 1),
						make_pair(0, -1),
						make_pair(1, 0),
						make_pair(-1, 0),
						make_pair(1, 1),
						make_pair(-1, 1),
						make_pair(-1, -1),
						make_pair(1, -1)
					};

					for (int c=0;c<8;c++){
						bool is_check = true;
						int now_piece_grid_y = piece_grid_y;
						int now_piece_grid_x = piece_grid_x;

						while (is_check){
							now_piece_grid_y += directions[c].first;
							now_piece_grid_x += directions[c].second;

							if (now_piece_grid_y >= 0 && now_piece_grid_y <= BOARDHEIGHT-1 && now_piece_grid_x >= 0 && now_piece_grid_x <= BOARDWIDTH-1){
								if (board_pieces_lst[now_piece_grid_y][now_piece_grid_x] == "empty"){
									path_pos_lst.push_back(make_pair(now_piece_grid_y, now_piece_grid_x));
								}
								else{
									if (split(board_pieces_lst[now_piece_grid_y][now_piece_grid_x], '-')[1] != piece_side){
										attack_pos_lst.push_back(make_pair(now_piece_grid_y, now_piece_grid_x));
									}
									is_check = false;
								}
							}
							else{
								is_check = false;
							}

						}
					}
				}


				else if (piece_name == "king"){
					// 上方
					if (piece_grid_y >= 1){
						if (board_pieces_lst[piece_grid_y-1][piece_grid_x] == "empty"){
							path_pos_lst.push_back(make_pair(piece_grid_y-1, piece_grid_x));
						}
						else{
							if (split(board_pieces_lst[piece_grid_y-1][piece_grid_x], '-')[1] != piece_side){
								attack_pos_lst.push_back(make_pair(piece_grid_y-1, piece_grid_x));
							}
						}
					}
					// 下方
					if (piece_grid_y <= BOARDHEIGHT-2){
						if (board_pieces_lst[piece_grid_y+1][piece_grid_x] == "empty"){
							path_pos_lst.push_back(make_pair(piece_grid_y+1, piece_grid_x));
						}
						else{
							if (split(board_pieces_lst[piece_grid_y+1][piece_grid_x], '-')[1] != piece_side){
								attack_pos_lst.push_back(make_pair(piece_grid_y+1, piece_grid_x));
							}
						}
					}
					// 左侧
					if (piece_grid_x >= 1){
						if (board_pieces_lst[piece_grid_y][piece_grid_x-1] == "empty"){
							path_pos_lst.push_back(make_pair(piece_grid_y, piece_grid_x-1));
						}
						else{
							if (split(board_pieces_lst[piece_grid_y][piece_grid_x-1], '-')[1] != piece_side){
								attack_pos_lst.push_back(make_pair(piece_grid_y, piece_grid_x-1));
							}
						}
					}
					// 右侧
					if (piece_grid_x <= BOARDWIDTH-2){
						if (board_pieces_lst[piece_grid_y][piece_grid_x+1] == "empty"){
							path_pos_lst.push_back(make_pair(piece_grid_y, piece_grid_x+1));
						}
						else{
							if (split(board_pieces_lst[piece_grid_y][piece_grid_x+1], '-')[1] != piece_side){
								attack_pos_lst.push_back(make_pair(piece_grid_y, piece_grid_x+1));
							}
						}
					}
				}


				// 根据 path_pos_lst 和 attack_pos_lst 绘制指示圆圈
				for (size_t a=0;a<path_pos_lst.size();a++){
					int x_pos = path_pos_lst[a].second * GRIDWIDTH + GRIDWIDTH / 2;
					int y_pos = path_pos_lst[a].first * GRIDHEIGHT + GRIDHEIGHT / 2;
					Circle new_circle(&path_circle_img, &path_circle_mask_img, x_pos, y_pos, path_pos_lst[a].second, path_pos_lst[a].first, pieces_group[i].id, "path");
					circles_group.push_back(new_circle);
				}
				for (size_t a=0;a<attack_pos_lst.size();a++){
					int x_pos = attack_pos_lst[a].second * GRIDWIDTH + GRIDWIDTH / 2;
					int y_pos = attack_pos_lst[a].first * GRIDHEIGHT + GRIDHEIGHT / 2;
					Circle new_circle(&attack_circle_img, &attack_circle_mask_img, x_pos, y_pos, attack_pos_lst[a].second, attack_pos_lst[a].first, pieces_group[i].id, "attack");
					circles_group.push_back(new_circle);
				}
			}
		}

		for (size_t i=0;i<circles_group.size();i++){
			circles_group[i].draw();
		}

		FlushBatchDraw();

		Sleep(10);
	}

	_getch();

	closegraph();

	return 0;

}
