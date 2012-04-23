class CreateUsers < ActiveRecord::Migration
  def change
    create_table :users do |t|
      t.string :name
      t.string :email
      t.boolean :admin, :default=>false
      t.string :third_party_id
      t.integer :login_count, :default=>0
      t.datetime :last_login

      t.timestamps
    end
  end
end
