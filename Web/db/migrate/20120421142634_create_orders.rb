class CreateOrders < ActiveRecord::Migration
  def change
    create_table :orders do |t|
      t.references :drink
      t.references :user
      t.boolean :completed, :default=>false
      t.timestamps
    end
  end
end
