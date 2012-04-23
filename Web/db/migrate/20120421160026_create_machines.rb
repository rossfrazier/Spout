class CreateMachines < ActiveRecord::Migration
  def change
    create_table :machines do |t|
      t.boolean :active
      t.integer :drinks_count

      t.timestamps
    end
    Machine.create(:active=>false, :drinks_count=>0)
  end
end
