#pragma once

class ClientEntityListener
{
public:
	virtual void OnEntityCreated(CEntity* entity) = 0;
	virtual void OnEntityDeleted(CEntity* entity) = 0;
};

class IClientEntityList {
public:
	constexpr CEntity* GetEntityFromIndex(const int32_t index) noexcept {
		return memory::Call<CEntity*>(this, 3, index);
	}
	/*constexpr CEntity* GetClientEntityFromHandle(BaseHandle handle) noexcept {
		return memory::Call<CEntity*>(this, 4, handle);
	}*/
	constexpr int NumberOfEntities(bool includeNonNetworkable) noexcept {
		return memory::Call<int>(this, 5, includeNonNetworkable);
	}
	constexpr int GetHighestEntityIndex() noexcept {
		return memory::Call<int>(this, 6);
	}
	constexpr void SetMaxEntities(int maxEntities) noexcept {
		return memory::Call<void, int>(this, 7, maxEntities);
	}
	constexpr int GetMaxEntities() noexcept {
		return memory::Call<int>(this, 8);
	}

	template <typename T = CEntity>
	constexpr T* Get(int index) {
		return static_cast<T*>(GetEntityFromIndex(index));
	}

	void AddEntityListener(ClientEntityListener* listener)
	{
		//listeners.AddToTail(listener);
	}

	void RemoveEntityListener(ClientEntityListener* listener)
	{
		//listeners.FindAndRemove(listener);
	}

private:
	UtlVector<ClientEntityListener*> listeners;

};