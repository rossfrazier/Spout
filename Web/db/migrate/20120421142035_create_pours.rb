class CreatePours < ActiveRecord::Migration
  def change
    create_table :pours do |t|
      t.references :drink
      t.references :ingredient
      t.decimal :seconds

      t.timestamps
    end
  end
end
