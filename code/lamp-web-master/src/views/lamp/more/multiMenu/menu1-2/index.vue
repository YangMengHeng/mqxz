<template>
  <div style="padding:30px;">
    我是菜单1-2

    下面开始表演我有那些权限：

    <el-button
      v-has-permission="['authority:parameter:add', 'authority:parameter:e2dit','authority:parameter:delete']"
      class="filter-item"
      plain
      type="danger"
    >
      has 我有这里的所有权限1
    </el-button>
    <el-button
      v-has-permission="['authority:user:add', 'authority:parameter:add']"
      class="filter-item"
      plain
      type="danger"
    >
      has 我有这里的所有权限2
    </el-button>

    <el-button
      v-has-any-permission="['authority:123:add', 'authority:parameter:edit','authority:1234:delete']"
      class="filter-item"
      plain
      type="danger"
    >
      has any 我有这里的任意权限1
    </el-button>
    <el-button
      v-has-any-permission="['authority:user:add']"
      class="filter-item"
      plain
      type="danger"
    >
      has any 我有这里的任意权限2
    </el-button>

    <el-button
      v-has-no-permission="['authority:user:add', 'authority:4:edit','authority:5:delete']"
      class="filter-item"
      plain
      type="danger"
    >
      has no 我没有这里的所有权限1
    </el-button>
    <el-button
      v-has-no-permission="['authority:user:add']"
      class="filter-item"
      plain
      type="danger"
    >
      has no 我没有这里的所有权限2
    </el-button>


    <el-button
      v-has-role="['admin']"
      class="filter-item"
      plain
      type="danger"
    >
      has role 1
    </el-button>
    <el-button
      v-has-role="['ROLE_SUPER_ADMIN']"
      class="filter-item"
      plain
      type="danger"
    >
      has role 2
    </el-button>
    <el-button
      v-has-any-role="['ROLE_SUPER_AdMIN']"
      class="filter-item"
      plain
      type="danger"
    >
      has any role 1
    </el-button>
    <el-button
      v-has-any-role="['SUPER_ADMIN']"
      class="filter-item"
      plain
      type="danger"
    >
      has any role 2
    </el-button>
    <el-button
      v-has-no-role="['ROLE_SUPer_ADMIN']"
      class="filter-item"
      plain
      type="danger"
    >
      has no role 1
    </el-button>
    <el-button
      v-has-no-role="['SUPER_ADMIN']"
      class="filter-item"
      plain
      type="danger"
    >
      has no role 2
    </el-button>
  </div>
</template>
