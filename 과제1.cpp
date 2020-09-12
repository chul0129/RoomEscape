#include<bangtal.h>
using namespace bangtal;

int main() {
	//장면을 생성
	auto scene1 = Scene::create("룸1", "Images/배경-1.png");
	auto scene2 = Scene::create("룸2", "Images/배경-2.png");

	//문을 만든다.
	auto door1 = Object::create("Images/문-오른쪽-닫힘.png",scene1,800,270);
	auto door2 = Object::create("Images/문-왼쪽-열림.png", scene2, 320, 270);
	auto door3 = Object::create("Images/문-오른쪽-닫힘.png", scene2, 1200, 230,false);
	door3->setScale(0.3f);
	//스위치를 만든다.
	auto button = Object::create("Images/스위치.jpg", scene2, 870, 440);
	button->setScale(0.2f);
	
	door1->setOnMouseCallback([&](ObjectPtr, int x, int y, MouseAction action)->bool {
		
		door1->setImage("Images/문-오른쪽-열림.png");
		scene2->enter();
		showMessage("숨겨진 문을 찾아보세요!");
		return true;
		});

	door2->setOnMouseCallback([&](ObjectPtr, int x, int y, MouseAction action)->bool {
		scene1->enter();
		return true;
		});

	auto lighted = true;
	button->setOnMouseCallback([&](ObjectPtr, int x, int y, MouseAction action)->bool {
		if (lighted)
		{
			scene2->setLight(0.3f);
			lighted = false;
			door3->show();
		}
		else{
			scene2->setLight(1.0f);
			lighted = true;
			door3->hide();
		}

		return true;
		});
	door3->setOnMouseCallback([&](ObjectPtr, int x, int y, MouseAction action)->bool {
		if (lighted==false) {
	
			endGame();
		}
				return true;
		});

	startGame(scene1);
	return 0;
}