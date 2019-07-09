# Object-Oriented-project
# 面向对象编程
# Group project
# A Card game like Hearthstone using C++

Virtual class card has its name and basic property field : attack and defence---common part for all type of #card.

Using mainly inheritance  for the card with same type of feature, I write them as one type of structure, all this type of card with detail feature belong to this general type; 

The minion card are the simplest type card, beside the field same as general card. it got a field called cost, Player’s total cost are limited in one round and using minion to attack opponents will minus the cost the player own. Once the cost goes to 0. Player cannot use more minions in this round.

The enhancement card have another field that enhance that can be used to give other card enhancement  ,also it got the special description field to let player understand how to use this card. Those enhancement are likely to decorate minion card to change defence and attack, Some of the enhancement can change the cost and let more minion to be used in one round

Another type of card used to decorate is  called Ritual card. It’s used to decorate the player. Not specifically for one minion but to limit the next choice of opponents. For example . A card called Stand still. It will destroy the next minion the opponent use no matter what it is . It also has type description. Different from enhancement card. It has one more field called magic. Which is similar to ability but limit the number of ritual card to be used in one turn.

The last type of card is Spell. It’s a type of  card for some special use. For example to deal 2 damage to all minions not only opponents but yours. Or reborn the latest destroyed card.
 
Decorate pattern are used when using enhancement card  and Ritual card. Since the main job for enhancement card is to change the minion’s property. And Ritual is to change the player’s property.  Also, graphic display is build with observe pattern, Once player play a card the change among current data will be observed and show the reaction on the graphic display.  


