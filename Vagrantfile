Vagrant.configure(2) do |config|

  config.vm.box = "bento/ubuntu-12.04"

  config.vm.provider "virtualbox" do |vb|
    #   # Display the VirtualBox GUI when booting the machine
    #   vb.gui = true
    #
    #   # Customize the amount of memory on the VM:
    vb.memory = "1524"
    vb.name = "sec"
  end

  config.vm.network "private_network", ip: "192.168.5.1"
end
