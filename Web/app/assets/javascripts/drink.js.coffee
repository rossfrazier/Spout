class Drink.Model extends Backbone.Model

class Drink.Collection extends Backbone.Collection
	model: Drink.Model
	url: '/drinks'

class Drink.Views.List extends Backbone.View
	drinks = new Drink.Collection

class Drink.Views.Item extends Backbone.View
	tagName: 'tr'
	template: _.template($('#drinkItemTemplate').html())