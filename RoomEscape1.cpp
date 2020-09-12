#include <bangtal.h>
using namespace bangtal;

int main()
{
	//1.장면을 생성한다.
	auto scene1 = Scene::create("룸1", "Images/배경-1.png");
	auto scene2= Scene::create("룸2", "Images/배경-2.png");

	//열쇠를 만든다.
	auto key= Object::create("Images/열쇠.png", scene1, 600, 150);
	
	
	key->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		key->pick();
		return true;

		});
	//화분을 만든다.
	auto flowerpot_moved = false;
	auto flowerpot = Object::create("Images/화분.png", scene1, 550, 150);
	flowerpot->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (flowerpot_moved == false) {
			if (action == MouseAction::MOUSE_DRAG_LEFT) {
				flowerpot->locate(scene1, 450, 150);
				flowerpot_moved = true;
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				flowerpot->locate(scene1, 650, 150);
				flowerpot_moved = true;
			}
		}
		return true;
		});

	// 3. 문을 생성한다.
	auto open1 = false;
	
	auto door1 = Object::create("Images/문-오른쪽-닫힘.png",scene1,800,270);

	//4. 문을 클릭하면 이동한다. 
	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		//5.문이 열린 상태이면 게임을 종료한다.
		//  문이 닫힌 상태이면 문을 열어준다.
		if (open1==true)	//문이 열린 상태
		{
			scene2->enter();
		}
		else if(key->isHanded())	//문이 닫힌 상태
		{
			door1->setImage("Images/문-오른쪽-열림.png");
			open1 = true;
		}
		else {
			showMessage("열쇠가 필요해!!");
		}
		
		return true;
		});
	auto door2 = Object::create("Images/문-왼쪽-열림.png", scene2, 320, 270);
	door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene1->enter();
		return true;
		});
	auto open3 = false,locked3=true;
	auto door3 = Object::create("Images/문-오른쪽-닫힘.png", scene2, 910, 270);
	door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (locked3) {
			showMessage("문이 잠겨있다.");
		}
		else if (open3 == true) {
			endGame();
		}
		else {
			door3->setImage("Images/문-오른쪽-열림.png");
			open3 = true;
		}
		return true;
		});
	door3->setOnKeypadCallback([&](ObjectPtr object)->bool {
		locked3 = false;
		showMessage("철커덕~~~");
		return true;
	});
	auto keypad = Object::create("Images/열쇠.png", scene2, 875, 420);
	keypad->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showKeypad("BANGTAL", door3);
		return true;
		});
	auto password = Object::create("Images/암호.png", scene2, 400, 100,false);
	password->setScale(0.3f);

	auto lighted = true;
	auto button = Object::create("Images/스위치.jpg", scene2, 870, 440);
	button->setScale(0.2f);
	button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (lighted) {		//켜진상태
		scene2->setLight(0.2f);
		lighted = false;
		password->show();
		}
		else {
			scene2->setLight(1.0f);
			lighted = true;
			password->hide();
		}
		return true;
		});
	//2. 게임을 시작한다.
	startGame(scene1);
	return 0;

}