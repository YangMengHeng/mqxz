<template>
  <div id="app">
    <museum></museum>
  </div>
</template>

<script>
import museum from './components/museum.vue'

export default {
  name: 'App',
  components: {
    museum
  }
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
