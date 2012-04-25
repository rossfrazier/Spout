class CreateDrinks < ActiveRecord::Migration
  def change
    create_table :drinks do |t|
      t.string :name
      t.references :user
      t.integer :served_count
      t.binary :image
      t.timestamps
    end
  end
end
