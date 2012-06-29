class CreateMachines < ActiveRecord::Migration
  def change
    create_table :machines do |t|
      t.boolean :active
      t.integer :drinks_count
      t.boolean :chomping, :default=>false
      t.string :ip_address

      t.timestamps
    end
  end
end
