#include <vector>
#include <iostream>

const int x=1, y=2, z=4;

class CollisionBuffer{
	public:
		CollisionBuffer(size_t cap = 3) : 
			capacity(cap){
			idx=-1;
			data.resize(capacity);
			collisions=0;
		}
		void add(int newGuy){
			idx=(idx+1)%capacity;
			data[idx] = newGuy;
			collisions |= newGuy;
		}
		void print(){
			std::vector<int>::iterator it;
			for (it=data.begin(); it!=data.end(); it++){
				switch(*it){
					case x: std::cout << "x" << std::endl; break;
					case y: std::cout << "y" << std::endl; break;
					case z: std::cout << "z" << std::endl; break;
					default: std::cout << -1 << std::endl; break;
				}
			}
		}
		int last(){//idx should be the last thing added
			return data[idx];
		}
	
		bool collisionDetected(){
			return collisions == (x|y|z);
		}

	//Note that in the case of two simultaneous truths the order becomes (arbitrarily) x y z
		bool handleIt(bool colX, bool colY, bool colZ){
			if (colX){//if collision
				if (~collisions & x){//if it wasn't already noticed
					add(x);
					collisions |= x;
				}
			}
			else //otherwise remove from bit vec
				collisions &= ~x;

         if (colY){
            if (~collisions & y){
               add(y);
               collisions |= y;
            }
         }
         else
            collisions &= ~y;

         if (colZ){
            if (~collisions & z){
               add(z);
               collisions |= z;
            }
         }
         else
            collisions &= ~z;

			return collisionDetected();

		}
	private:
		size_t capacity;
		int idx;
		std::vector<int> data;
		int collisions;
};

int main(){
	CollisionBuffer buf;

	bool colX, colY, colZ;

	colX = false; colY = false; colZ = false;
	if (buf.handleIt(colX, colY, colZ))
		std::cout << buf.last() << std::endl;

	colX = false; colY = true; colZ = true;
   if (buf.handleIt(colX, colY, colZ))
      std::cout << buf.last() << std::endl;
	

   colX = true; colY = true; colZ = true;
   if (buf.handleIt(colX, colY, colZ))
		std::cout << buf.last() << std::endl;

	return 1;
}
