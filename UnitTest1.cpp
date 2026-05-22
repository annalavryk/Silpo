#include "pch.h"
#include "CppUnitTest.h"
#include "Silpo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{
	TEST_CLASS(UnitTestProject)
	{
	public:

		// Перевірка додавання товару в корзину
		TEST_METHOD(AddProductTest)
		{
			Order order;

			order.setDate("10.05", -1);

			// Додаємо 2 молока по 50 грн
			order.addProduct("Milk", 50, 2, 0);

			// Очікувана сума: 100
			Assert::AreEqual(100.0, order.getTotal());
		}

		// Перевірка додавання однакового товару
		TEST_METHOD(AddSameProductTest)
		{
			Order order;

			order.setDate("10.05", -1);

			// Додаємо товар двічі
			order.addProduct("Milk", 50, 2, 0);
			order.addProduct("Milk", 50, 3, 0);

			// Загальна сума: 250
			Assert::AreEqual(250.0, order.getTotal());
		}

		// Перевірка видалення товару
		TEST_METHOD(RemoveProductTest)
		{
			Order order;

			order.setDate("10.05", -1);

			order.addProduct("Bread", 30, 1, 0);

			// Видаляємо товар
			order.removeProduct("Bread");

			// Після видалення сума повинна бути 0
			Assert::AreEqual(0.0, order.getTotal());
		}

		// Перевірка зміни кількості товару
		TEST_METHOD(ChangeQuantityTest)
		{
			Order order;

			order.setDate("10.05", -1);

			order.addProduct("Apple", 10, 2, 0);

			// Змінюємо кількість товару
			order.changeQuantity("Apple", 7);

			// 7 * 10 = 70
			Assert::AreEqual(70.0, order.getTotal());
		}

		// Перевірка підрахунку загальної суми
		TEST_METHOD(TotalPriceTest)
		{
			Order order;

			order.setDate("10.05", -1);

			order.addProduct("Milk", 50, 2, 0);
			order.addProduct("Bread", 30, 1, 1);

			// 100 + 30 = 130
			Assert::AreEqual(130.0, order.getTotal());
		}

		// Перевірка застосування знижки
		TEST_METHOD(DiscountTest)
		{
			Order order;

			// Товар з індексом 1 має знижку
			order.setDate("10.05", 1);

			order.addProduct("Bread", 100, 1, 1);

			// Після знижки 10% -> 90 грн
			Assert::AreEqual(90.0, order.getTotal());
		}
	};
}