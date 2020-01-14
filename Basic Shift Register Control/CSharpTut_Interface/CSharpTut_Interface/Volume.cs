using System;


namespace CSharpTut_Interface
{
    class Volume : ICommand
    {
        IElectronicDevice device;
        public Volume(IElectronicDevice device)
        {
            this.device = device;
        }
      
        public void Execute()
        {
            device.VolumeUp();
        }

        public void Undo()
        {
            device.VolumeDown();
        }
    }
}
