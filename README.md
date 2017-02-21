# FireBase (Qt)

Firebase представляет собой мобильную платформу, которая позволяет быстро разрабатывать высококачественные приложения.
Для использования библиотеки необходимо иметь аккаунт Firebase.

### Возможности
      Отправлятть единичные данные
      Отправлять объекты данных
      Редактировать данные
      Удалять данные
      Перезаписывать данные
      Получать данные
      Получать отсортированные данные


*Выборка данных происходит только по одному параметру. 
Это техническая сторона FireBase. На момент написания данной библиотеки их ответ 
по вопросу о возможности выборки по нескольим данным был следующим:*

Thank you for your patience. Like you, there are other developers requesting for these features. 
In fact, there's already an existing internal request to address this functionality. But as of the moment, no public release dates or details we can share.

#### Установка

Установка библиотеки является стандартной установкой сторонних библиотек в Qt. Необходимо скачать исодники и собрать библиотеку под свою систему. Далее следуя док-ции Qt подключить её к своему проекту.

Пример кода:
```с++
    QString http = "https://test.firebaseio.com/";
    QString token = "SECRET KEY";
    FireBase firebase(http, token);

```
### Запись данных

#### Данный метод запишит данные с собственным ключом от FireBase.

```c++
    QString str = "Money";
    QJsonObject object;
    object["value"] = 25345685;
    object["story"] = "many";
    firebase.child(str)->value(object)->push();

```

#### Данный метод запишит данные используя ваш ключ.
```c++
    QString str = "MY_KEY/Money";
    QJsonObject object;
    object["value"] = 25345685;
    object["story"] = "many";
    firebase.child(str)->value(object)->set();

```
#### Редактирование данных
```c++
    QString str = "Money";
    QJsonObject object;
    object["value"] = 25;    
    firebase.child(str)->value(object)->update();

```
#### Удаление данных
```c++
    QString str = "Money";
    firebase.child(str)->remove();
```

### Получение данных

```c++
    QString str = "Money";
    QString data = firebase.child(str)->get();
```

### Сортировка
Для сортировки данных необходимо на стороне FIreBase создать правила.

- *orderBy* - параметр по которому сортируем
- *startAt* - например, от 100 и выше
- *limitToFirst* - например, первые 20 отсортированных
- *endAt* - например до 100 и ниже
- *limitToLast* - последние 20 отсортированных

Пример кода когда нужно получить первые 100 записей по параметру "value" зачение которого не менее 10 000
```c++
    QString str = "Money";
    QString orderBy = "value";
    QString data = firebase.child(str)->orderBy(orderBy)->startAt(10000)->limitToFirst(100)->get();
```
Пример кода когда нужно получить последние 100 записей по параметру "value" зачение которого менее 10 000
```c++
    QString str = "Money";
    QString orderBy = "value";
    QString data = firebase.child(str)->orderBy(orderBy)->endAt(10000)->limitToLast(100)->get();
```

### LECENSE
See LICENSE.txt for details.

