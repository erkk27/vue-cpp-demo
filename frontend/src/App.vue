<script setup>
import { ref } from 'vue'

const message = ref('Click the button to fetch data from the C++ backend.')
const error = ref(null)

async function fetchMessage() {
  error.value = null
  try {
    const response = await fetch('/api/message')
    if (!response.ok) {
      throw new Error(`HTTP error! status: ${response.status}`)
    }
    const data = await response.json()
    message.value = data.message
  } catch (e) {
    error.value = e.message
    message.value = 'Failed to fetch message.'
  }
}

// Alternative method that directly accesses the backend
async function fetchMessageDirect() {
  error.value = null
  try {
    const response = await fetch('http://127.0.0.1:18080/api/message')
    if (!response.ok) {
      throw new Error(`HTTP error! status: ${response.status}`)
    }
    const data = await response.json()
    message.value = data.message + ' (direct)'
  } catch (e) {
    error.value = e.message
    message.value = 'Failed to fetch message.'
  }
}
</script>

<template>
  <header>
    <h1>Vue 3 + C++ Backend</h1>
  </header>

  <main>
    <div class="card">
      <p>{{ message }}</p>
      <button @click="fetchMessage">Fetch Message (Proxy)</button>
      <button @click="fetchMessageDirect" style="margin-left: 10px;">Fetch Message (Direct)</button>
      <p v-if="error" class="error">Error: {{ error }}</p>
    </div>
  </main>
</template>

<style scoped>
header {
  line-height: 1.5;
}

main {
  display: flex;
  justify-content: center;
  align-items: center;
  height: 50vh;
}

.card {
  text-align: center;
  padding: 2em;
  border-radius: 12px;
  background-color: var(--color-background-soft);
  box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
}

button {
  margin-top: 1em;
  padding: 0.5em 1em;
  border: none;
  border-radius: 4px;
  background-color: hsla(160, 100%, 37%, 1);
  color: white;
  cursor: pointer;
  font-size: 1em;
}

button:hover {
  background-color: hsla(160, 100%, 37%, 0.8);
}

.error {
  margin-top: 1em;
  color: #e53e3e; /* A reddish color for errors */
}
</style> 